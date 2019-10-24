// Copyright (C) 2018 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import * as m from 'mithril';

import {Actions} from '../common/actions';
import {TrackState} from '../common/state';

import {globals} from './globals';
import {drawGridLines} from './gridline_helper';
import {Panel, PanelSize} from './panel';
import {verticalScrollToTrack} from './scroll_helper';
import {Track} from './track';
import {TRACK_SHELL_WIDTH} from './track_constants';
import {trackRegistry} from './track_registry';
import {
  drawVerticalLineAtTime,
  drawVerticalSelection
} from './vertical_line_helper';

function isPinned(id: string) {
  return globals.state.pinnedTracks.indexOf(id) !== -1;
}

interface TrackShellAttrs {
  track: Track;
  trackState: TrackState;
}

class TrackShell implements m.ClassComponent<TrackShellAttrs> {
  // Set to true when we click down and drag the
  private dragging = false;
  private dropping: 'before'|'after'|undefined = undefined;
  private attrs?: TrackShellAttrs;

  oninit(vnode: m.Vnode<TrackShellAttrs>) {
    this.attrs = vnode.attrs;
  }

  view({attrs}: m.CVnode<TrackShellAttrs>) {
    // The shell should be highlighted if the current search result is inside
    // this track.
    let highlightClass = '';
    const searchIndex = globals.frontendLocalState.searchIndex;
    if (searchIndex !== -1) {
      const trackId = globals.currentSearchResults
                          .trackIds[globals.frontendLocalState.searchIndex];
      if (trackId === attrs.trackState.id) {
        highlightClass = 'flash';
      }
    }

    const dragClass = this.dragging ? `drag` : '';
    const dropClass = this.dropping ? `drop-${this.dropping}` : '';
    return m(
        `.track-shell[draggable=true]`,
        {
          class: `${highlightClass} ${dragClass} ${dropClass}`,
          onmousedown: this.onmousedown.bind(this),
          ondragstart: this.ondragstart.bind(this),
          ondragend: this.ondragend.bind(this),
          ondragover: this.ondragover.bind(this),
          ondragleave: this.ondragleave.bind(this),
          ondrop: this.ondrop.bind(this),
        },
        m('h1',
          {
            title: attrs.trackState.name,
          },
          attrs.trackState.name),
        attrs.track.getTrackShellButtons(),
        m(TrackButton, {
          action: () => {
            globals.dispatch(
                Actions.toggleTrackPinned({trackId: attrs.trackState.id}));
          },
          i: isPinned(attrs.trackState.id) ? 'star' : 'star_border',
          tooltip: isPinned(attrs.trackState.id) ? 'Unpin' : 'Pin to top',
          selected: isPinned(attrs.trackState.id),
        }));
  }

  onmousedown(e: MouseEvent) {
    // Prevent that the click is intercepted by the PanAndZoomHandler and that
    // we start panning while dragging.
    e.stopPropagation();
  }

  ondragstart(e: DragEvent) {
    const dataTransfer = e.dataTransfer;
    if (dataTransfer === null) return;
    this.dragging = true;
    globals.rafScheduler.scheduleFullRedraw();
    dataTransfer.setData('perfetto/track', `${this.attrs!.trackState.id}`);
    dataTransfer.setDragImage(new Image(), 0, 0);
    e.stopImmediatePropagation();
  }

  ondragend() {
    this.dragging = false;
    globals.rafScheduler.scheduleFullRedraw();
  }

  ondragover(e: DragEvent) {
    if (this.dragging) return;
    if (!(e.target instanceof HTMLElement)) return;
    const dataTransfer = e.dataTransfer;
    if (dataTransfer === null) return;
    if (!dataTransfer.types.includes('perfetto/track')) return;
    dataTransfer.dropEffect = 'move';
    e.preventDefault();

    // Apply some hysteresis to the drop logic so that the lightened border
    // changes only when we get close enough to the border.
    if (e.offsetY < e.target.scrollHeight / 3) {
      this.dropping = 'before';
    } else if (e.offsetY > e.target.scrollHeight / 3 * 2) {
      this.dropping = 'after';
    }
    globals.rafScheduler.scheduleFullRedraw();
  }

  ondragleave() {
    this.dropping = undefined;
    globals.rafScheduler.scheduleFullRedraw();
  }

  ondrop(e: DragEvent) {
    if (this.dropping === undefined) return;
    const dataTransfer = e.dataTransfer;
    if (dataTransfer === null) return;
    globals.rafScheduler.scheduleFullRedraw();
    const srcId = dataTransfer.getData('perfetto/track');
    const dstId = this.attrs!.trackState.id;
    globals.dispatch(Actions.moveTrack({srcId, op: this.dropping, dstId}));
    this.dropping = undefined;
  }
}

export interface TrackContentAttrs { track: Track; }
export class TrackContent implements m.ClassComponent<TrackContentAttrs> {
  view({attrs}: m.CVnode<TrackContentAttrs>) {
    return m('.track-content', {
      onmousemove: (e: MouseEvent) => {
        attrs.track.onMouseMove({x: e.layerX, y: e.layerY});
        globals.rafScheduler.scheduleRedraw();
      },
      onmouseout: () => {
        attrs.track.onMouseOut();
        globals.rafScheduler.scheduleRedraw();
      },
      onclick: (e: MouseEvent) => {
        // If we are selecting a time range - do not pass the click to the
        // track.
        if (e.shiftKey) return;
        // If the click is outside of the current time range, clear it.
        const clickTime =
            globals.frontendLocalState.timeScale.pxToTime(e.layerX);
        const start = globals.frontendLocalState.selectedTimeRange.startSec;
        const end = globals.frontendLocalState.selectedTimeRange.endSec;
        if (start !== undefined && end !== undefined &&
            (clickTime < start || clickTime > end)) {
          globals.frontendLocalState.removeTimeRange();
          e.stopPropagation();
        } else if (attrs.track.onMouseClick({x: e.layerX, y: e.layerY})) {
          e.stopPropagation();
        }
        globals.rafScheduler.scheduleRedraw();
      }
    });
  }
}

interface TrackComponentAttrs {
  trackState: TrackState;
  track: Track;
}
class TrackComponent implements m.ClassComponent<TrackComponentAttrs> {
  view({attrs}: m.CVnode<TrackComponentAttrs>) {
    return m(
        '.track',
        {
          style: {
            height: `${attrs.track.getHeight()}px`,
          },
          id: 'track_' + attrs.trackState.id,
        },
        [
          m(TrackShell, {track: attrs.track, trackState: attrs.trackState}),
          m(TrackContent, {track: attrs.track})
        ]);
  }

  onupdate({attrs}: m.CVnode<TrackComponentAttrs>) {
    if (globals.frontendLocalState.scrollToTrackId === attrs.trackState.id) {
      verticalScrollToTrack(attrs.trackState.id);
      globals.frontendLocalState.scrollToTrackId = undefined;
    }
  }
}

export interface TrackButtonAttrs {
  action: () => void;
  i: string;
  tooltip: string;
  selected: boolean;
}
export class TrackButton implements m.ClassComponent<TrackButtonAttrs> {
  view({attrs}: m.CVnode<TrackButtonAttrs>) {
    return m(
        'i.material-icons.track-button',
        {
          class: `${attrs.selected ? 'show' : ''}`,
          onclick: attrs.action,
          title: attrs.tooltip,
        },
        attrs.i);
  }
}

interface TrackPanelAttrs {
  id: string;
}

export class TrackPanel extends Panel<TrackPanelAttrs> {
  private track: Track;
  private trackState: TrackState;
  constructor(vnode: m.CVnode<TrackPanelAttrs>) {
    super();
    this.trackState = globals.state.tracks[vnode.attrs.id];
    const trackCreator = trackRegistry.get(this.trackState.kind);
    this.track = trackCreator.create(this.trackState);
  }

  view() {
    return m(TrackComponent, {trackState: this.trackState, track: this.track});
  }

  renderCanvas(ctx: CanvasRenderingContext2D, size: PanelSize) {
    ctx.save();
    drawGridLines(
        ctx,
        globals.frontendLocalState.timeScale,
        globals.frontendLocalState.visibleWindowTime,
        size.width,
        size.height);

    ctx.translate(TRACK_SHELL_WIDTH, 0);

    this.track.render(ctx);

    ctx.restore();

    const localState = globals.frontendLocalState;
    // Draw vertical line when hovering on the notes panel.
    if (localState.showNotePreview) {
      drawVerticalLineAtTime(ctx,
                             localState.timeScale,
                             localState.hoveredTimestamp,
                             size.height,
                             `#aaa`);
    }
    // Draw vertical line when shift is pressed.
    if (localState.showTimeSelectPreview) {
      drawVerticalLineAtTime(ctx,
                             localState.timeScale,
                             localState.hoveredTimestamp,
                             size.height,
                             `rgb(52,69,150)`);
    }
    if (globals.frontendLocalState.selectedTimeRange.startSec !== undefined &&
        globals.frontendLocalState.selectedTimeRange.endSec !== undefined) {
      drawVerticalSelection(
          ctx,
          localState.timeScale,
          globals.frontendLocalState.selectedTimeRange.startSec,
          globals.frontendLocalState.selectedTimeRange.endSec,
          size.height,
          `rgba(0,0,0,0.5)`);
    }
    if (globals.state.currentSelection !== null) {
      if (globals.state.currentSelection.kind === 'NOTE') {
        const note = globals.state.notes[globals.state.currentSelection.id];
        drawVerticalLineAtTime(ctx,
                               localState.timeScale,
                               note.timestamp,
                               size.height,
                               note.color);
      }
      if (globals.state.currentSelection.kind === 'SLICE' &&
          globals.sliceDetails.wakeupTs !== undefined) {
        drawVerticalLineAtTime(
            ctx,
            localState.timeScale,
            globals.sliceDetails.wakeupTs,
            size.height,
            `black`);
      }
    }
  }
}
