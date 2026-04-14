import { useEffect, useState } from 'react';
import { useHoldKey } from './useHoldKey';
import { socket } from '../socket';

export const useTankControl = () => {
  const [action, setAction] = useState<TankControlAction>('stop');

  const handlePress = (action: TankControlAction) => {
    socket.send(JSON.stringify({ action }));
  };

  useHoldKey(handlePress);

  useEffect(() => {
    socket.onmessage = (event) => {
      const data: TankState = JSON.parse(event.data);

      if (data.action !== undefined) {
        setAction(data.action);
      }
    };

    return () => {
      socket.onmessage = null;
    };
  }, []);

  console.log(action);

  return { action };
};
