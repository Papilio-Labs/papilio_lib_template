#!/usr/bin/env python3
"""
Run all tests (simulation + hardware) for papilio_template

Top-level test runner that coordinates both simulation and hardware tests.

Usage:
    python run_all_tests.py              # Run all tests
    python run_all_tests.py --sim-only   # Run only simulation tests
    python run_all_tests.py --hw-only    # Run only hardware tests
"""

import sys
import subprocess
import argparse
from pathlib import Path


def run_simulation_tests():
    """Run simulation tests"""
    print("\n" + "="*60)
    print("Running Simulation Tests")
    print("="*60)
    
    sim_dir = Path(__file__).parent / "tests" / "sim"
    sim_runner = sim_dir / "run_all_sims.py"
    
    if not sim_runner.exists():
        print(f"Simulation tests not found: {sim_runner}")
        return False
    
    result = subprocess.run([sys.executable, str(sim_runner)], cwd=str(sim_dir))
    return result.returncode == 0


def run_hardware_tests():
    """Run hardware tests with PlatformIO"""
    print("\n" + "="*60)
    print("Running Hardware Tests")
    print("="*60)
    
    hw_dir = Path(__file__).parent / "tests" / "hw"
    
    if not hw_dir.exists():
        print(f"Hardware tests not found: {hw_dir}")
        return False
    
    # Check if platformio.ini exists
    if not (hw_dir / "platformio.ini").exists():
        print(f"No platformio.ini found in {hw_dir}")
        print("Hardware tests not configured")
        return True  # Not a failure, just not configured
    
    result = subprocess.run(["pio", "test"], cwd=str(hw_dir))
    return result.returncode == 0


def main():
    parser = argparse.ArgumentParser(description="Run all tests for papilio_template")
    parser.add_argument("--sim-only", action="store_true", 
                       help="Run only simulation tests")
    parser.add_argument("--hw-only", action="store_true",
                       help="Run only hardware tests")
    args = parser.parse_args()
    
    print("="*60)
    print("Papilio Template - Test Runner")
    print("="*60)
    
    sim_pass = True
    hw_pass = True
    
    # Run simulation tests
    if not args.hw_only:
        sim_pass = run_simulation_tests()
    
    # Run hardware tests
    if not args.sim_only:
        hw_pass = run_hardware_tests()
    
    # Summary
    print("\n" + "="*60)
    print("Overall Test Summary")
    print("="*60)
    
    if not args.hw_only:
        status = "[PASS]" if sim_pass else "[FAIL]"
        print(f"{status}: Simulation Tests")
    
    if not args.sim_only:
        status = "[PASS]" if hw_pass else "[FAIL]"
        print(f"{status}: Hardware Tests")
    
    overall_pass = sim_pass and hw_pass
    print(f"\nOverall: {'PASS' if overall_pass else 'FAIL'}")
    
    return 0 if overall_pass else 1


if __name__ == "__main__":
    sys.exit(main())
