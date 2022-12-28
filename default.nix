with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "8bit";
  nativeBuildInputs = [pkg-config];
  buildInputs = [ SDL2 SDL2_ttf];
}
