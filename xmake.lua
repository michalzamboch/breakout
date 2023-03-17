add_rules("mode.debug", "mode.release")
set_languages("c11")
set_warnings("all", "error")

add_requires("libsdl", "libsdl_ttf")

target("breakout")
    set_kind("binary")

    add_files("src/*.c")
    add_packages("libsdl", "libsdl_ttf")
    add_includedirs("include")
    
    after_build(function (target)
        print("\nTarget: %s", target:name())
        print("Target file: %s", target:targetfile())
        os.cp("fonts", target:targetdir())
    end)

