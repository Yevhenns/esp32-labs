import { useEffect, useState, type FC } from 'react';
import { useHoldKey } from '../../hooks/useHoldKey';
import { socket } from '../../socket';
import { Button } from '../Button/Button';
import сrab from '../../assets/crab.svg';
import css from './GripperControl.module.css';

export const GripperControl: FC = () => {
  const [action, setAction] = useState<GripperControlAction>('stop');

  const handlePress = (action: GripperControlAction) => {
    socket.send(JSON.stringify({ action }));
  };

  useHoldKey(handlePress);

  useEffect(() => {
    socket.onmessage = (event) => {
      const data: GripperState = JSON.parse(event.data);
      console.log(data);

      if (data.action !== undefined) {
        setAction(data.action);
      }
    };

    return () => {
      socket.onmessage = null;
    };
  }, []);

  return (
    <div className={css.container}>
      <h1 className={css.title}>ESP32 Robotic Gripper</h1>

      <img src={сrab} alt="crab" width={128} />

      <div className={css.action}>
        Action: <b>{action}</b>
      </div>

      <div className={css.controls}>
        <Button type="grab" handlePress={handlePress}>
          ✊ Grab (W)
        </Button>
        <Button type="release" handlePress={handlePress}>
          ✋ Release (S)
        </Button>
      </div>
    </div>
  );
};
