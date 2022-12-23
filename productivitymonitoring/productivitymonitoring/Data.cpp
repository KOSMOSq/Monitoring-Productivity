#include "Data.h"

//void DeleteHeader(std::wstring& text) {
//	if (text.size() == 0)
//	{
//		return;
//	}
//	auto number = text.find(':') + 2; // До : и +2 символа, что бы удалить : и ' '
//	text.erase(text.begin(), text.begin() + number);
//}

wistream& operator>> (wistream& is, CPU& cpu)
{
	is.ignore(2);
	std::getline(is, cpu.name);
	//DeleteHeader(cpu.name);
	std::getline(is, cpu.Manufacturer);
	//DeleteHeader(cpu.Manufacturer);
	std::getline(is, cpu.NumberOfLogicalProcessors);
	//DeleteHeader(cpu.NumberOfLogicalProcessors);
	std::getline(is, cpu.NumberofCores);
	//DeleteHeader(cpu.NumberofCores);
	std::getline(is, cpu.CurrentClockSpeed);
	//DeleteHeader(cpu.CurrentClockSpeed);
	std::getline(is, cpu.LoadPercentage);
	//DeleteHeader(cpu.LoadPercentage);
	std::getline(is, cpu.L2CacheSize);
	//DeleteHeader(cpu.L2CacheSize);
	std::getline(is, cpu.L3CacheSize);
	//DeleteHeader(cpu.L3CacheSize);
	
	return is;
}

wistream& operator>> (wistream& is, DISK& disk)
{
	is.ignore(1);
	std::getline(is, disk.name);
	DeleteHeader(disk.name);
	std::getline(is, disk.MediaType);
	DeleteHeader(disk.MediaType);
	std::getline(is, disk.BusType);
	DeleteHeader(disk.BusType);
	std::getline(is, disk.Size);
	DeleteHeader(disk.Size);
	return is;
}

wistream& operator>> (wistream& is, VOLUME& volume)
{
	is.ignore(1);
	std::getline(is, volume.DriveLetter);
	DeleteHeader(volume.DriveLetter);
	std::getline(is, volume.FileSystemLabel);
	DeleteHeader(volume.FileSystemLabel);
	std::getline(is, volume.FileSystemType);
	DeleteHeader(volume.FileSystemType);
	std::getline(is, volume.Size);
	DeleteHeader(volume.Size);
	std::getline(is, volume.SizeRemaining);
	DeleteHeader(volume.SizeRemaining);
	return is;
}

wistream& operator>> (wistream& is, GPU& gpu)
{
	is.ignore(2);
	std::getline(is, gpu.name);
	DeleteHeader(gpu.name);
	std::getline(is, gpu.CurrentHorizontalResolution);
	DeleteHeader(gpu.CurrentHorizontalResolution);
	std::getline(is, gpu.MaxRefreshRate);
	DeleteHeader(gpu.MaxRefreshRate);
	std::getline(is, gpu.CurrentVerticalResolution);
	DeleteHeader(gpu.CurrentVerticalResolution);
	std::getline(is, gpu.AdapterRAM);
	DeleteHeader(gpu.AdapterRAM);
	return is;
}

wistream& operator>> (wistream& is, RAM& ram)
{
	is.ignore(1);
	std::getline(is, ram.Manufacturer);
	DeleteHeader(ram.Manufacturer);
	std::getline(is, ram.PartNumber);
	DeleteHeader(ram.PartNumber);
	std::getline(is, ram.SerialNumber);
	DeleteHeader(ram.SerialNumber);
	std::getline(is, ram.DeviceLocator);
	DeleteHeader(ram.DeviceLocator);
	std::getline(is, ram.Capacity);
	DeleteHeader(ram.Capacity);
	std::getline(is, ram.Speed);
	DeleteHeader(ram.Speed);
	return is;
}