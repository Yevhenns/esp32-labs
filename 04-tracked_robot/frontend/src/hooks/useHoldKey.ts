import { useEffect, useRef } from 'react';

type Callback = (action: TankControlAction) => void;

export const useHoldKey = (callback: Callback) => {
  const keysPressed = useRef<Record<string, boolean>>({});

  useEffect(() => {
    const forwardKeys = ['w', 'W', 'ц', 'Ц'];
    const backwardKeys = ['s', 'S', 'і', 'І', 'ы', 'Ы'];
    const leftKeys = ['a', 'A', 'ф', 'Ф'];
    const rightKeys = ['d', 'D', 'в', 'В'];

    const handleKeyDown = (e: KeyboardEvent) => {
      if (keysPressed.current[e.key]) return;
      keysPressed.current[e.key] = true;

      if (forwardKeys.includes(e.key)) callback('forward');
      if (backwardKeys.includes(e.key)) callback('backward');
      if (leftKeys.includes(e.key)) callback('left');
      if (rightKeys.includes(e.key)) callback('right');
    };

    const handleKeyUp = (e: KeyboardEvent) => {
      keysPressed.current[e.key] = false;

      if (forwardKeys.includes(e.key)) callback('stop');
      if (backwardKeys.includes(e.key)) callback('stop');
      if (leftKeys.includes(e.key)) callback('stop');
      if (rightKeys.includes(e.key)) callback('stop');
    };

    window.addEventListener('keydown', handleKeyDown);
    window.addEventListener('keyup', handleKeyUp);

    return () => {
      window.removeEventListener('keydown', handleKeyDown);
      window.removeEventListener('keyup', handleKeyUp);
    };
  }, [callback]);
};
