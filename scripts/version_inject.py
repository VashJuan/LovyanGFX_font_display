#!/usr/bin/env python3
"""
PlatformIO extra script to inject git version into build
"""

Import("env")
import subprocess
import os


def get_git_version():
    """Get git version using git describe"""
    project_dir = env.get("PROJECT_DIR")
    print(f"Project directory: {project_dir}")

    try:
        # Check if we're in a git repository
        result = subprocess.run(
            ["git", "status", "--porcelain"],
            capture_output=True,
            text=True,
            cwd=project_dir,
        )
        if result.returncode != 0:
            print("Not in a git repository")
            return "v2.0.1-nogit"

        # Try to get git version with tags
        result = subprocess.run(
            ["git", "describe", "--tags", "--always", "--dirty"],
            capture_output=True,
            text=True,
            cwd=project_dir,
        )
        print(
            f"Git describe result: returncode={result.returncode}, stdout='{result.stdout}', stderr='{result.stderr}'"
        )

        if result.returncode == 0:
            version = result.stdout.strip()
            if version:
                print(f"Got version from git describe: {version}")
                return version

        # Fallback to commit hash
        result = subprocess.run(
            ["git", "rev-parse", "--short", "HEAD"],
            capture_output=True,
            text=True,
            cwd=project_dir,
        )
        print(
            f"Git rev-parse result: returncode={result.returncode}, stdout='{result.stdout}', stderr='{result.stderr}'"
        )

        if result.returncode == 0:
            hash_val = result.stdout.strip()
            if hash_val:
                version = f"dev-{hash_val}"
                print(f"Using commit hash version: {version}")
                return version

    except FileNotFoundError:
        print("Git command not found")
        return "v2.0.1-nogit"
    except Exception as e:
        print(f"Git version detection failed: {e}")

    # Ultimate fallback - if no git or git fails
    print("Using ultimate fallback version")
    return "v2.0.1"


# Get version and inject it
version = get_git_version()
print(f"Injecting version: {version}")

# Remove any existing PROJECT_VERSION definition and add the new one
env.Append(CPPDEFINES=[("PROJECT_VERSION", f'\\"{version}\\"')])

# Also set it as a global define for consistent access
env.Append(CPPDEFINES=[("GIT_VERSION", f'\\"{version}\\"')])
