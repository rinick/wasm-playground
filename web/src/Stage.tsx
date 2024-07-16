import React from 'react';
import ResizeObserver from 'resize-observer-polyfill';
import classNames from 'classnames';

interface Props {
  delay: number;
}
interface State {
  imgW: number;
  imgH: number;
  canvasScale: 'h' | 'v' | 's';
  pixelated: boolean;
}

export class Stage extends React.PureComponent<Props, State> {
  state: State = {imgW: 256, imgH: 256, canvasScale: 'h', pixelated: true};
  resizeObserver: any;

  timeout: any;

  startTimer = () => {
    if (this.timeout) {
      clearTimeout(this.timeout);
      this.timeout = null;
    }
    if (!this.mounted) {
      return;
    }

    let {delay} = this.props;
    if (delay != Infinity) {
      this.timeout = setTimeout(this.update, delay);
    }
  };

  update =  () => {
    if (this._canvasNode) {
      const context = this._canvasNode.getContext('2d');
      const Module = (window as any).Module as any;
      if (!Module) {
        return;
      }
      const uarr = new Uint8ClampedArray(Module.HEAP8.buffer, Module._run(), 256*256*4);
      const imageData = new ImageData(uarr, 256,256);
      context.putImageData(imageData, 0, 0);
    }
    this.startTimer();
  };

  _rootNode!: HTMLElement;
  getRootRef = (node: HTMLDivElement): void => {
    this._rootNode = node;
  };

  _canvasNode!: HTMLCanvasElement;
  getCanvasRef = (c: HTMLCanvasElement): void => {
    this._canvasNode = c;
  };

  checkResize(width: number, height: number) {
    let {imgW, imgH} = this.state;
    width *= window.devicePixelRatio;
    height *= window.devicePixelRatio;
    let imgR = imgW / imgH;
    let stageR = width / height;
    let pixelated = width > imgW * 1.75 && height > imgH * 1.75;
    if (stageR >= imgR) {
      this.setState({canvasScale: 'h', pixelated});
    } else {
      this.setState({canvasScale: 'v', pixelated});
    }
  }
  handleResize = (entries: ResizeObserverEntry[]) => {
    let {width, height} = entries[0].contentRect;
    this.checkResize(width, height);
  };
  forceResize() {
    this.checkResize(this._rootNode.offsetWidth, this._rootNode.offsetHeight);
  }

  mounted = false;
  componentDidMount() {
    this.resizeObserver = new ResizeObserver(this.handleResize);
    this.resizeObserver.observe(this._rootNode);
    this.mounted = true;
    this.startTimer();
  }


  render() {

    let {imgW, imgH, canvasScale, pixelated} = this.state;

    let style: any = null;

    this.startTimer();

    let stageCls = classNames('amoeba-stage', `stage-scale-${canvasScale}`);
    let canvasCls = classNames('amoeba-canvas', `canvas-scale-${canvasScale}`, {pixelated: pixelated});
    return (
      <div className={stageCls} ref={this.getRootRef}>
        <canvas
          className={canvasCls}
          ref={this.getCanvasRef}
          width={imgW}
          height={imgH}
          style={style}
        />
      </div>
    );
  }

  componentWillUnmount() {
    if (this.timeout) {
      clearTimeout(this.timeout);
    }
    this.mounted = false;
  }
}
