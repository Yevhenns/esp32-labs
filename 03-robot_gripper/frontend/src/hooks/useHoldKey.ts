import { useEffect, useRef } from 'react';

type Callback = (action: GripperControlAction) => void;

export const useHoldKey = (callback: Callback) => {
  const keysPressed = useRef<Record<string, boolean>>({});

  useEffect(() => {
    const pushKeys = ['w', 'W', 'ц', 'Ц'];
    const releaseKeys = ['s', 'S', 'і', 'І', 'ы', 'Ы'];

    const handleKeyDown = (e: KeyboardEvent) => {
      if (keysPressed.current[e.key]) return;
      keysPressed.current[e.key] = true;

      if (pushKeys.includes(e.key)) callback('grab');
      if (releaseKeys.includes(e.key)) callback('release');
    };

    const handleKeyUp = (e: KeyboardEvent) => {
      keysPressed.current[e.key] = false;

      if (pushKeys.includes(e.key)) callback('stop');
      if (releaseKeys.includes(e.key)) callback('stop');
    };

    window.addEventListener('keydown', handleKeyDown);
    window.addEventListener('keyup', handleKeyUp);

    return () => {
      window.removeEventListener('keydown', handleKeyDown);
      window.removeEventListener('keyup', handleKeyUp);
    };
  }, [callback]);
};
