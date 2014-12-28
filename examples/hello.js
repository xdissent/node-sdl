var path = require('path'),
  sdl = require('../sdl');

try {

  sdl.init(sdl.INIT.EVERYTHING);

  var win = new sdl.Window('Hello World!', undefined, undefined, 640, 480, sdl.WINDOW.FULLSCREEN);
  var ren = new sdl.Renderer(win, -1, sdl.RENDERER.ACCELERATED | sdl.RENDERER.PRESENTVSYNC);
  var xxx = new sdl.Surface(1, 1);
  var bmp = xxx.loadBMP(path.join(__dirname, 'hello.bmp'));
  var tex = new sdl.Texture(ren, bmp);

  ren.clear();
  ren.copy(tex);
  ren.present();

} catch (err) {
  console.error('CAUGHT ERROR', err);
  sdl.quit();
  process.exit(1);
}

setTimeout(function () {
  console.log('QUITTING');
  sdl.quit();
}, 2000);
