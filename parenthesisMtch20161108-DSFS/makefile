PWD=.
project_name=example
TARGET=$(project_name)

init:
	@[ -d include ] || (mkdir include && mv *.h include)
	@[ -d bin ] || mkdir bin
	@[ -d lib ] || mkdir lib

exclude_dirs= include  bin  lib

include $(PWD)/CPPMakefile.env
