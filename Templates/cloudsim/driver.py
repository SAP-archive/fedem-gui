"""
Python driver for Fedem cloud simulation apps.
This file needs to be copied into the lib folder of the app running Fedem.
"""

from glob import glob
from os import environ, getcwd, makedirs, path
from shutil import copytree

from fedempy.fmm_solver import FedemException, FmmSolver


def _get_out_dir():
    out_dir_env = environ.get("PEI_SERVICE_FILE_STORAGE")
    if out_dir_env is None:
        return "."
    out_dir = path.normcase(out_dir_env)
    if not path.isdir(out_dir):
        makedirs(out_dir)
    return out_dir


def run(lib_dir="/var/digitaltwin/app/lib"):
    """
    Run fedem simulation and extract output files.

    Parameters
    ----------
    lib_dir : str
        Absolute path to app location with model file
    """

    if not path.isdir(lib_dir):
        lib_dir = getcwd()

    # Find model file
    fmm_files = glob(lib_dir + "/*.fmm")
    if not fmm_files:
        raise FedemException(f"No fmm-files in {lib_dir}")

    # Initialize the solver
    solver = FmmSolver()

    # Solve the model
    ierr = solver.solve_all(path.abspath(fmm_files[0]), True, True)

    # Copy results to output folder, if any
    rdb_dirs = glob(lib_dir + "/*_RDB/response*")
    if rdb_dirs:
        response_folder = path.abspath(rdb_dirs[0])
        copytree(response_folder, _get_out_dir() + "/results/")

    if ierr != 0:
        raise FedemException(f"Failed to run solver ({ierr})")


if __name__ == "__main__":
    run(".")
