import React from 'react';

import {Stage} from './Stage';


interface State {



}

export class App extends React.PureComponent<any, State> {
  state: State = { };

  _stage!: Stage;
  getStageRef = (s: Stage): void => {
    this._stage = s;
  };


  render() {


    return (
      <div className="stage-layout">
        <div>
          <Stage  ref={this.getStageRef} delay={50} />
        </div>
      </div>
    );
  }
}
