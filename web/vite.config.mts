import {defineConfig, normalizePath} from 'vite';
import Path from 'path'
import react from '@vitejs/plugin-react';
import {nodePolyfills} from 'vite-plugin-node-polyfills';
import {viteStaticCopy} from 'vite-plugin-static-copy';

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react(), nodePolyfills(),  viteStaticCopy({
    targets: [
      {
        src: normalizePath(Path.resolve(__dirname, '../build/WebAssembly_Qt_6_7_2_single_threaded-Debug/wasm-playground.*')),
        dest: 'wasm'
      }
    ]
  })],
  base: '',
  server: {
    hmr: false,
  },
  root: "src",
  build: {
    outDir: '../dist',
    emptyOutDir: true,
    rollupOptions: {
      output: {
        entryFileNames: `assets/[name].js`,
        chunkFileNames: `assets/[name].js`,
        assetFileNames: `assets/[name].[ext]`,
      }
    },
  },
});
