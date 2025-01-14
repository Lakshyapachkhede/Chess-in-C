# Debug flag
$debug = $true  # Set to $false for no console

# Directories and files
$sourceDir = ".\src"
$outputDir = ".\bin"
$outputFile = "chess.exe"
$includeDirs = @(".\include", ".\libs\include")
$libDir = ".\libs\lib"
$sdlDlls = @("SDL2.dll", "SDL2_image.dll", "SDL2_mixer.dll", "SDL2_ttf.dll")

# Ensure output directory exists
if (!(Test-Path -Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir
}

# Get all source files
$sourceFiles = Get-ChildItem -Path $sourceDir -Filter "*.c" | ForEach-Object { $_.FullName }
if (-not $sourceFiles) {
    Write-Host "No source files found in $sourceDir" -ForegroundColor Red
    exit 1
}

# Compiler setup
$compiler = "gcc"
$includeFlags = ($includeDirs | ForEach-Object { "-I`"$_`"" }) -join " "
$compileFlags = "-L`"$libDir`" -lmingw32 -lSDL2main -L$sourceDir -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -std=c99 -Wall"
$compileCommand = "$compiler $($sourceFiles -join ' ') $includeFlags $compileFlags -o `"$outputDir\$outputFile`""

# If debug is false, suppress console output (for Windows, use -mwindows for GUI apps)
if (-not $debug) {
    $compileFlags += " -mwindows"
}


# Compilation
Write-Host "Compiling..." -ForegroundColor Yellow
Write-Host "Command: $compileCommand" -ForegroundColor Cyan
Invoke-Expression -Command $compileCommand

if ($LASTEXITCODE -ne 0) {
    Write-Host "Compilation failed!" -ForegroundColor Red
    exit 1
}

Write-Host "Compilation successful. Output: $outputDir\$outputFile" -ForegroundColor Green

# Copy SDL DLLs to output
foreach ($dll in $sdlDlls) {
    $dllPath = Join-Path -Path $sourceDir -ChildPath $dll
    if (Test-Path $dllPath) {
        Copy-Item -Path $dllPath -Destination $outputDir
        Write-Host "Copied $dll to $outputDir" -ForegroundColor Green
    } else {
        Write-Host "Warning: $dll not found in $sourceDir" -ForegroundColor Yellow
    }
}

# Run the program
Write-Host "Running the program..." -ForegroundColor Yellow
Start-Process -FilePath ".\$outputFile" -WorkingDirectory $outputDir

