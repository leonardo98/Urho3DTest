1. copy folder "bin" from Urho3D to this folder
2. create folder "build"
3. cd build
4. cmake .. -G "Xcode" -DURHO3D_HOME=<folder to builded Urho3D>


EXAMPLE (for my iMac): > cmake .. -G "Xcode" -DURHO3D_HOME=~/work/Urho3D-1.6/build/