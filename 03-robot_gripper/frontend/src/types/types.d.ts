type GripperCommand = 'grab' | 'release';

type GripperControlAction = GripperCommand | 'stop';

type GripperState = {
  action: GripperControlAction;
};
