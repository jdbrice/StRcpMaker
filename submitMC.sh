#!/bin/bash

starver SL14i

unlink grid.xml 
ln -s grid/mc/grid_K_Minus.xml grid.xml
star-submit grid.xml

unlink grid.xml 
ln -s grid/mc/grid_K_Plus.xml grid.xml
star-submit grid.xml

unlink grid.xml 
ln -s grid/mc/grid_Pi_Plus.xml grid.xml
star-submit grid.xml

unlink grid.xml 
ln -s grid/mc/grid_Pi_Minus.xml grid.xml
star-submit grid.xml

unlink grid.xml 
ln -s grid/mc/grid_Proton.xml grid.xml
star-submit grid.xml

unlink grid.xml 
ln -s grid/mc/grid_PBar.xml grid.xml
star-submit grid.xml

