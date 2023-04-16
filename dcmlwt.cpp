#include <fstream>
#include <iostream>

int main() {
    std::ifstream file("/Users/ryanmarr/Downloads/raycaster_test/t/IM-0001-0348.dcm", std::ios::binary);
    if (!file) {
        // Handle file opening error.
    }

    // Read the file contents into a buffer.
    file.seekg(0, std::ios::end);
    auto file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(file_size);
    file.read(buffer.data(), file_size);

    // Verify the DICOM file marker.
    if (std::string(buffer.data(), 4) != "DICM") {
        std::cout << (buffer.data(), 4);
        std::cout << "NOT DICM";
    }
    else {
        std::cout << "DICM";
    }

    // Parse the DICOM file and extract the patient name.
    std::uint32_t tag;
    std::string vr;
    std::uint32_t length;
    std::string patient_name;
    std::size_t offset = 0;
    while (offset < buffer.size()) {
        std::memcpy(&tag, buffer.data() + offset, sizeof(tag));
        offset += sizeof(tag);
        std::memcpy(&vr, buffer.data() + offset, sizeof(vr));
        offset += sizeof(vr);
        std::memcpy(&length, buffer.data() + offset, sizeof(length));
        offset += sizeof(length);
        std::cout << tag << " ";
        if (tag == 0x00100010) { // Patient's Name
            patient_name.resize(length);
            std::memcpy(reinterpret_cast<void*>(const_cast<char*>(patient_name.data())), buffer.data() + offset, length);
            break;
        }

        offset += length;
    }

    // Use the patient name.
    std::cout << "Patient name: " << patient_name << std::endl;

    return 0;
}