# `mv`ing `f`iles

> Moves directories and files to `/tmp` for faster execution than `rm -rf`

## Why

To finally get a native reason program running in 2022.

## Usage

```shell
# Provide a mixed list of directories and/or files
$ mvf node_modules dist tmp-file.txt
```

## Environment setup

1. Ensure you have `esy` installed and available globally

```shell
$ pnpm i --global esy
```

2. Bootstrap with `esy`

[install deps and build.](https://esy.sh/docs/en/commands.html#esy)

```shell
$ esy
```

## Building

To emit the executable we use `esy` to run `dune` to get the right resolutions to the reason libraries we link in the `dune` file.

```shell
$ esy dune build
```

This will compile source into an executable to `./_esy/default/build/default/src/Main.exe` — mirroring the `src` directory structure.

## Running the executable

For full OS permissions, run the built executable directly instead of using `esy`

```shell
$ ./_esy/default/build/default/src/Main.exe node_modules dist
```

## Development

The following command will execute the program with `esy`, but this is a sandboxed environment and will not allow the program to have filesystem access.

```shell
$ esy b dune exec ./Main.exe
```
