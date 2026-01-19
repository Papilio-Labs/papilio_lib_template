#!/usr/bin/env python3
"""
Run all simulation tests for papilio_template

Uses papilio_dev_tools infrastructure for cross-platform simulation.
IMPORTANT: Always use this script - never invoke iverilog/vvp directly!

Usage:
    python run_all_sims.py
"""

import sys
import os
from pathlib import Path

# Add papilio_dev_tools scripts to path
# Navigate from tests/sim/ up to workspace libs/ directory
dev_tools_scripts = Path(__file__).parent.parent.parent.parent / "papilio_dev_tools" / "scripts"
sys.path.insert(0, str(dev_tools_scripts))

# Import run_sim module
try:
    import run_sim
except ImportError:
    print("Error: Could not import run_sim from papilio_dev_tools", file=sys.stderr)
    print(f"Looking in: {dev_tools_scripts}", file=sys.stderr)
    print("\nMake sure papilio_dev_tools library is available:", file=sys.stderr)
    print("  - In PlatformIO workspace: Should be in libs/papilio_dev_tools", file=sys.stderr)
    print("  - Standalone: Adjust path to papilio_dev_tools location", file=sys.stderr)
    sys.exit(1)


def main():
    print("="*60)
    print("Papilio Template - Simulation Tests")
    print("="*60)
    
    # Set up environment (handles OSS CAD Suite on Windows)
    oss_cad_path = run_sim.setup_environment()
    
    # Define gateware sources
    gateware_dir = Path(__file__).parent.parent.parent / "gateware"
    
    # Find the main Verilog module (papilio_*.v)
    module_files = list(gateware_dir.glob("papilio_*.v"))
    if not module_files:
        print(f"Error: No papilio_*.v module found in: {gateware_dir}", file=sys.stderr)
        sys.exit(1)
    
    module_file = module_files[0]  # Use first match
    print(f"Using module: {module_file.name}")
    
    # Find all testbenches (tb_*.v)
    testbenches = sorted(Path(__file__).parent.glob("tb_*.v"))
    
    if not testbenches:
        print("No testbenches found (no tb_*.v files)")
        return 0
    
    print(f"\nFound {len(testbenches)} testbench(es):")
    for tb in testbenches:
        print(f"  - {tb.name}")
    
    # Run each testbench
    results = []
    for tb in testbenches:
        print(f"\n{'='*60}")
        print(f"Running: {tb.name}")
        print('='*60)
        
        # Compile: testbench + module
        output = tb.with_suffix('.vvp')
        success = run_sim.compile_verilog(
            sources=[str(tb), str(module_file)],
            output=str(output),
            include_dirs=[str(gateware_dir)],
            standard="2012",
            oss_cad_path=oss_cad_path
        )
        
        if not success:
            results.append((tb.name, False))
            continue
        
        # Run simulation
        success = run_sim.run_simulation(str(output), oss_cad_path=oss_cad_path)
        results.append((tb.name, success))
    
    # Summary
    print(f"\n{'='*60}")
    print("Test Summary")
    print('='*60)
    
    passed = sum(1 for _, success in results if success)
    failed = len(results) - passed
    
    for tb_name, success in results:
        status = "[PASS]" if success else "[FAIL]"
        print(f"{status}: {tb_name}")
    
    print(f"\nTotal: {len(results)} | Passed: {passed} | Failed: {failed}")
    
    return 0 if failed == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
