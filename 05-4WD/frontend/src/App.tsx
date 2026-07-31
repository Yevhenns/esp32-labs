import './App.css';
import { useTankControl } from './hooks/useTankControl';

function App() {
  useTankControl();

  return (
    <>
      <section id="center">
        <div>
          <iframe src="http://192.168.0.112/stream" width="300" height="200" />
        </div>
      </section>

      <div className="ticks"></div>
      <section id="spacer"></section>
    </>
  );
}

export default App;
