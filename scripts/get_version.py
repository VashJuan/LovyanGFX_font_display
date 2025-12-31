#!/usr/bin/env python3
"""
Build script to inject git version into build
"""
import subprocess
import os


def get_git_version():
    """Get git version using git describe"""
    try:
        # Try to get git version
        result = subprocess.run(
            ["git", "describe", "--tags", "--always"],
            capture_output=True,
            text=True,
            cwd=os.path.dirname(__file__),
        )
        if result.returncode == 0:
            return result.stdout.strip()
        else:
            # Fallback to commit hash
            result = subprocess.run(
                ["git", "rev-parse", "--short", "HEAD"],
                capture_output=True,
                text=True,
                cwd=os.path.dirname(__file__),
            )
            if result.returncode == 0:
                return result.stdout.strip()
    except Exception:
        pass

    # Ultimate fallback
    return "unknown"


if __name__ == "__main__":
    version = get_git_version()
    print(f'-DPROJECT_VERSION=\\"{version}\\"')
