type TankCommand = 'forward' | 'backward' | 'left' | 'right';

type TankControlAction = TankCommand | 'stop';

type TankState = {
  action: TankControlAction;
};
