# Papilio Library Template

This is a template for creating new Papilio libraries that follow the Papilio Library Standards.

## Using This Template

### 1. Copy the Template

```powershell
# Copy to new library location
Copy-Item -Recurse libs/papilio_lib_template libs/papilio_your_library_name
cd libs/papilio_your_library_name
```

### 2. Rename Files

Use PowerShell to rename all template files:

```powershell
# Rename all files containing "Template" to your library name
# For example, to create "papilio_rgb_led":
$oldName = "Template"
$newName = "RgbLed"  # Use PascalCase for class names

Get-ChildItem -Recurse -File | Where-Object { $_.Name -match $oldName } | ForEach-Object {
    $newFileName = $_.Name -replace $oldName, $newName
    Rename-Item $_.FullName $newFileName
}
```

### 3. Replace Content Placeholders

Search and replace the following placeholders throughout all files:

| Placeholder | Replace With | Example |
|-------------|--------------|---------|
| `PapilioTemplate` | Your class name (PascalCase) | `PapilioRgbLed` |
| `PAPILIO_TEMPLATE` | Your header guard (SCREAMING_SNAKE_CASE) | `PAPILIO_RGB_LED` |
| `papilio_lib_template` | Your library name (snake_case) | `papilio_rgb_led` |
| `papilio_template` | Your module name (snake_case) | `papilio_rgb_led` |
| `template` | Your module short name (for CLI commands) | `rgbled` |

```powershell
# Use PowerShell to replace content
$files = Get-ChildItem -Recurse -File -Include *.h,*.cpp,*.ino,*.v,*.md,*.json,*.cst
foreach ($file in $files) {
    (Get-Content $file.FullName) `
        -replace 'PapilioTemplate', 'PapilioRgbLed' `
        -replace 'PAPILIO_TEMPLATE', 'PAPILIO_RGB_LED' `
        -replace 'papilio_lib_template', 'papilio_rgb_led' `
        -replace 'papilio_template', 'papilio_rgb_led' `
        -replace '\btemplate\b', 'rgbled' |
    Set-Content $file.FullName
}
```

### 4. Customize Each File

Review and customize:

- **library.json** - Update name, description, keywords, version, and **papilio metadata section**
  - Update gateware module information (file, parameters, description)
  - Specify Wishbone characteristics (address range, data width, burst support)
  - Document ESP32 class information
  - List CLI commands
- **README.md** - Document your library's purpose and API
- **AI_SKILL.md** - Add register maps and library-specific instructions
- **src/PapilioTemplate.h** - Define your public API
- **src/PapilioTemplate.cpp** - Implement your API
- **src/PapilioTemplateOS.h** - Define CLI commands (if applicable)
- **src/PapilioTemplateOS.cpp** - Implement CLI commands and tutorial
- **gateware/papilio_template.v** - Implement your Wishbone module
- **gateware/constraints/*.cst** - Define pin assignments for each board
- **gateware/README.md** - Document register map and hardware interface
- **tests/sim/*.v** - Write testbenches for your module
- **examples/TemplateCLI/TemplateCLI.ino** - Create example sketch

### 5. Add Board Support

For each Papilio board you support:

1. Create a constraint file in `gateware/constraints/<board_name>.cst`
2. Define all external pins used by your module
3. Include comments explaining each pin
4. Update README.md to list supported boards

Standard board names:
- `papilio_retrocade.cst` - Papilio Retrocade board
- `papilio_synth.cst` - Papilio Synth board

### 6. Update Papilio Metadata in library.json

The `papilio` section enables automatic library integration. Update these fields:

**Gateware:**
- `file` - Path to your Verilog module
- `module` - Module name as it appears in Verilog
- `parameters` - All configurable parameters with defaults
- `description` - Clear explanation of module purpose

**Wishbone:**
- `address_range` - How much address space your module needs (e.g., "32 bytes for 8 registers")
- `data_width` - Your data bus width (8, 16, 24, or 32)
- `burst_support` - `true` if you support burst transfers
- `features` - Array of supported operations

**ESP32:**
- `class` - Your C++ class name
- `headers` - Array of header files users need to include
- `init_params` - Parameters users pass to constructor
- `description` - Brief description of firmware API

**CLI:**
- `commands` - List all CLI commands with brief descriptions
- Update with your actual command list

This metadata enables:
- Automatic gateware discovery and inclusion in builds
- Board-specific constraint file selection
- Integration with future tooling and documentation generators

### 7. Test Your Library

```powershell
# Run simulation tests
cd tests/sim
python run_all_sims.py

# Run hardware tests (if applicable)
cd tests/hw
pio test

# Test example sketch
cd examples/TemplateCLI
pio run
```

### 8. Remove This File

After completing customization, delete `TEMPLATE_README.md` from your library.

## Directory Structure

```
papilio_your_library/
├── library.json                     # PlatformIO metadata
├── README.md                        # Library documentation
├── AI_SKILL.md                      # AI assistant instructions
├── src/                             # ESP32 firmware
│   ├── PapilioYourLibrary.h         # Main API header
│   ├── PapilioYourLibrary.cpp       # Main API implementation
│   ├── PapilioYourLibraryOS.h       # OS plugin (optional)
│   └── PapilioYourLibraryOS.cpp     # OS plugin implementation
├── gateware/                        # FPGA modules
│   ├── README.md                    # Hardware documentation
│   ├── papilio_your_library.v       # Main Verilog module
│   └── constraints/                 # Pin definitions
│       ├── papilio_retrocade.cst    # Retrocade pins
│       └── papilio_synth.cst        # Synth pins
├── tests/                           # Test infrastructure
│   ├── sim/                         # Simulation tests
│   │   ├── README.md
│   │   ├── tb_your_library.v
│   │   └── run_all_sims.py
│   └── hw/                          # Hardware tests
│       ├── README.md
│       └── platformio.ini
├── run_all_tests.py                 # Top-level test runner
└── examples/
    └── YourLibraryCLI/
        └── YourLibraryCLI.ino       # Example sketch
```

## Standards Compliance

This template follows the Papilio Library Standards defined in:
- OpenSpec: `openspec/specs/papilio-library-standards/`
- Documentation: See project `AGENTS.md` → "Papilio Library Standards" section

## Need Help?

- Review reference implementations: `papilio_wb_register`, `papilio_wishbone_bus`
- Check `papilio_dev_tools` for testing infrastructure patterns
- See `papilio_dev_tools/AI_SKILL.md` for development guidance
