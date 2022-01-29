function Format-CppSources {
    param (
        [SupportsWildcards()]
        [parameter(ParameterSetName="SpecificPathes")]
        [string[]]$Path,

        [parameter(ParameterSetName="AllFormat")]
        [switch]$All
    )

    if ($All) {
        [string[]]$SourceFiles = (Get-ChildItem -Path .\include\, .\src\, .\tests\ -Include "*.cpp", "*.hpp", "*.h", "*.c" -Recurse)
        clang-format.exe -i $SourceFiles
    } elseif ($Path) {
        Write-Error "Not implemented"
    }
}