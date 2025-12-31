#!/bin/bash
# update_version.sh - Script to update project version using git tags

# Check if version argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <version> (e.g., 2.0.2)"
    echo "This script will:"
    echo "  1. Update version in platformio.ini"
    echo "  2. Create git tag"
    echo "  3. Update README.md"
    exit 1
fi

VERSION=$1

# Validate version format (basic check)
if [[ ! $VERSION =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
    echo "Error: Version must be in format X.Y.Z (e.g., 2.0.2)"
    exit 1
fi

echo "Updating project to version $VERSION..."

# Update platformio.ini - replace all instances of PROJECT_VERSION
sed -i.bak "s/PROJECT_VERSION=\"[^\"]*\"/PROJECT_VERSION=\"v$VERSION\"/g" platformio.ini

# Update README.md versions section
sed -i.bak "/## 📋 Versions/,/^\*\*v[0-9]/c\\
## 📋 Versions\\
\\
**v$VERSION** - Latest release ($(date '+%Y-%m-%d'))\\
\\
**v2.0.1** - Minor updates and fixes (2025-12-30)\\
\\
**v2.0** - Second release (2025-12-30)\\
\\
**v1.0** - Initial release (2025-12-16)" README.md

# Update startup message reference in README
sed -i.bak "s/M5 Dial Font Display v[0-9.]\+/M5 Dial Font Display v$VERSION/g" README.md

echo "Files updated. To complete the version release:"
echo "  1. Review changes: git diff"
echo "  2. Commit changes: git add . && git commit -m 'Release v$VERSION'"
echo "  3. Create tag: git tag v$VERSION"
echo "  4. Push: git push origin main --tags"

# Optional: Show what would be changed
echo ""
echo "Changes made to platformio.ini:"
grep "PROJECT_VERSION" platformio.ini