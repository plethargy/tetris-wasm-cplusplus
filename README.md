# WASM Tetris

## Compilation
Download the files, make sure you have the Emscripten compiler configured and run the following command in the root directory of the tetris.cpp:
``` emcc -o tetris.html tetris.cpp -O1 -s WASM=1 --shell-file template/html_template.html -s NO_EXIT_RUNTIME=1  -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']" -s EXPORTED_FUNCTIONS="['_moveDown', '_moveLeft', '_clearBoard', '_moveRight', '_startGame', '_restartGame', '_rotateLeft', '_rotateRight', '_getScore', '_isGameOver', '_getGame']" ```

## Execution
Ensure that you have Python installed and in your PATH environment variable, the in the root folder of the tetris.html run the following command:
``` python -m http.server```
Then browse to localhost:8000 and select the tetris.html file in order to begin.
