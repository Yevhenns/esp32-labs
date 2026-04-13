import type { FC, HTMLProps, PropsWithChildren } from 'react';
import css from './Button.module.css';

type Props = {
  type: GripperCommand;
  handlePress: (action: GripperControlAction) => void;
} & HTMLProps<PropsWithChildren<HTMLButtonElement>>;

export const Button: FC<Props> = ({ children, type, handlePress }) => {
  return (
    <button
      className={css.btn + ' ' + css[type]}
      onMouseDown={() => handlePress(type)}
      onMouseUp={() => handlePress('stop')}
      onTouchStart={() => handlePress(type)}
      onTouchEnd={() => handlePress('stop')}
    >
      {children}
    </button>
  );
};
