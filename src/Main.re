let parse_args = () => {
  let raw_args = List.tl(Array.to_list(Sys.argv));

  raw_args;
};

let verify_mods = rgs => {
  let existing_mods = rgs |> List.filter(dir => Sys.file_exists(dir));

  existing_mods;
};

let safe_remove = (from, dest) => {
  switch (Sys.rename(from, dest)) {
  | () => Ok()
  | exception (Sys_error(_)) => Error("Unable to move")
  };
};

let mv_to_tmp = (os_tmp_dir, entry) => {
  let bits = Random.bits() |> Int.to_string;
  let is_file = !Sys.is_directory(entry);

  if (is_file) {
    safe_remove(entry, Filename.concat(os_tmp_dir, entry));
  } else {
    let tmp_dir_name = entry ++ "-" ++ bits;
    let tmp_dir = Filename.concat(os_tmp_dir, tmp_dir_name);
    safe_remove(entry, tmp_dir);
  };
};

let main = () => {
  let existing = parse_args() |> verify_mods;

  let msg =
    if (existing |> List.length > 0) {
      /* TODO: Print in a nicer format with icons for noting files and directories */
      existing
      |> List.map(x => {
           <Pastel underline=true bold=true> x </Pastel> |> Console.log
         })
      |> ignore;
      Console.log("About to move these modules, cool? [y/n]");

      switch (read_line()) {
      | "y"
      | "Y" =>
        Random.self_init();

        let os_tmp_dir = Filename.get_temp_dir_name();
        let mv = os_tmp_dir |> mv_to_tmp;

        let rec exec = entries => {
          switch (entries) {
          | [] => ()
          | [head, ...tail] =>
            switch (mv(head)) {
            | Ok () => exec(tail)
            | Error(_) => ()
            }
          };
        };

        exec(existing);

        <Pastel bold=true color=Green> "👍 All good" </Pastel>;
      | _ => <Pastel bold=true color=Cyan> "👋 Take care!" </Pastel>
      };
    } else {
      <Pastel bold=true color=Yellow> "No files matched" </Pastel>;
    };

  msg |> Console.log;
};

main();