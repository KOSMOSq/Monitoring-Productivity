//#pragma once
//#include <string>
//#include <fstream>
//
//using std::wstring;
//using std::wistream;
//using std::operator>>;
//
//class CPU
//{
//public:
//	wstring name;
//	wstring Manufacturer;
//	wstring NumberOfLogicalProcessors;
//	wstring NumberofCores;
//	wstring CurrentClockSpeed;
//	wstring LoadPercentage;
//	wstring L2CacheSize;
//	wstring L3CacheSize;
//
//};
//wistream& operator>> (wistream& is, CPU& cpu);
//
//class DISK
//{
//public:
//	wstring name;
//	wstring MediaType;
//	wstring BusType;
//	wstring Size;
//};
//wistream& operator>> (wistream& is, DISK& disk);
//
//class VOLUME
//{
//public:
//	wstring DriveLetter;
//	wstring FileSystemLabel;
//	wstring FileSystemType;
//	wstring Size;
//	wstring SizeRemaining;
//};
//wistream& operator>> (wistream& is, VOLUME& volume);
//
//class GPU
//{
//public:
//	wstring name;
//	wstring CurrentHorizontalResolution;
//	wstring MaxRefreshRate;
//	wstring CurrentVerticalResolution;
//	wstring AdapterRAM;
//};
//wistream& operator>> (wistream& is, GPU& gpu);
//
//class RAM
//{
//public:
//	wstring Manufacturer;
//	wstring PartNumber;
//	wstring SerialNumber;
//	wstring DeviceLocator;
//	wstring Capacity;
//	wstring Speed;
//};
//wistream& operator>> (wistream& is, RAM& ram);