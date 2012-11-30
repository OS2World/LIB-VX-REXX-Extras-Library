/**/

address cmd
"@echo off"
"setlocal"

if( directory( "som\sc" ) \= "" )then do
    'erase /n *.*'
end

if( directory( "..\..\obj" ) \= "" )then do
    'erase /n *.*'
end

if( directory( "..\objd" ) \= "" )then do
    'erase /n *.*'
end

"endlocal"
