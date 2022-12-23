Function Format-Bytes {
    Param
    (
        [Parameter(
            ValueFromPipeline = $true
        )]
        [ValidateNotNullOrEmpty()]
        [float]$number
    )
    Begin{
        $sizes = 'KB','MB','GB','TB','PB'
    }
    Process {
        if ($number -lt 1KB) {
            return "$number B"
        } elseif ($number -lt 1MB) {
            $number = $number / 1KB
            $number = "{0:N2}" -f $number
            return "$number KB"
        } elseif ($number -lt 1GB) {
            $number = $number / 1MB
            $number = "{0:N2}" -f $number
            return "$number MB"
        } elseif ($number -lt 1TB) {
            $number = $number / 1GB
            $number = "{0:N2}" -f $number
            return "$number GB"
        } elseif ($number -lt 1PB) {
            $number = $number / 1TB
            $number = "{0:N2}" -f $number
            return "$number TB"
        } else {
            $number = $number / 1PB
            $number = "{0:N2}" -f $number
            return "$number PB"
        }
    }
    End{}
}

Get-WmiObject Win32_Processor | fl Name, Manufacturer,NumberOfLogicalProcessors,NumberofCores,CurrentClockSpeed,LoadPercentage,@{N=’L2CacheSize’; E={Format-Bytes $_.L2CacheSize}},@{N=’L3CacheSize’; E={Format-Bytes $_.L3CacheSize}} | Out-File -FilePath CPU.txt -Encoding ASCII

Get-PhysicalDisk | fl Model,MediaType,BusType,@{N=’Size’; E={Format-Bytes $_.Size}} | Out-File -FilePath DISK.txt -Encoding ASCII

Get-Volume | Where {$_.DriveLetter -match "^[A-Z]"} | Sort-Object DriveLetter | fl DriveLetter, FileSystemLabel ,FileSystemType, @{N=’Size’; E={Format-Bytes $_.Size}}, @{N=’SizeRemaining’; E={Format-Bytes $_.SizeRemaining}} | Out-File -FilePath VOLUME.txt -Encoding ASCII

Get-WmiObject Win32_VideoController | fl Name, CurrentHorizontalResolution, MaxRefreshRate, CurrentVerticalResolution, @{N=’AdapterRAM’; E={Format-Bytes $_.AdapterRAM}} | Out-File -FilePath GPU.txt -Encoding ASCII

Get-WmiObject Win32_PhysicalMemory | fl Manufacturer, PartNumber, SerialNumber, DeviceLocator, @{N=’Capacity’; E={Format-Bytes $_.Capacity}}, Speed | Out-File -FilePath RAM.txt -Encoding ASCII

$Data =  Get-WmiObject -Class WIN32_OperatingSystem
$MemoryUsage = ((($Data.TotalVisibleMemorySize - $Data.FreePhysicalMemory)*100)/ $Data.TotalVisibleMemorySize)
$MemoryUsage = "{0:N2}" -f $MemoryUsage
$MemoryUsage | Out-File -FilePath RAMUsage.txt -Encoding ASCII