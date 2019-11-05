from cpt.packager import ConanMultiPackager

if __name__ == "__main__":
    builder = ConanMultiPackager(
        # package id
        username = "uilianries",
        channel = "testing",
        stable_branch_pattern = r"master",

        # dependencies
        remotes = None,
        build_policy = "outdated",
        upload_dependencies="all",

        # build configurations
        archs = ["x86_64"], #  limit to 64-bit only

        # package upload (REMEMBER to set CONAN_PASSWORD environment variable in Travis CI and AppVeyor)
        login_username = "uilianries",
        upload = "https://api.bintray.com/conan/uilianries/conan"
    )
    builder.add_common_builds(pure_c=False)
    for settings, options, env_vars, build_requires, reference in builder.items:
        settings["compiler.cppstd"] = "20"
    builder.run()
