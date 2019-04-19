# from distutils.core import setup
from setuptools import setup, find_packages

setup(name='pylib',
        author="Lei Wang (yiak.wy@gmail.com)",
        version='0.1.0',
        package_dir={'': "/Users/wangyi/GitHub/Leetcode/problems/Onsite-Blackboard Code Interview/airbnb/P1/python"},
        packages=find_packages(),
        entry_points={
            'console_scripts': [
                'pysol = lib.solution:main'
                ]
            },
        description="Pyhton lib")


