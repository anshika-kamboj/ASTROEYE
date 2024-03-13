#include <bits/stdc++.h>

using namespace std;

class CelestialObject {
public:
    CelestialObject(double ra, double dec, double mag, string name)
        : m_rightAscension(ra), m_declination(dec), m_magnitude(mag), m_name(name)
    {}

    double getRightAscension() const { return m_rightAscension; }
    double getDeclination() const { return m_declination; }
    double getMagnitude() const { return m_magnitude; }
    string getName() const { return m_name; }
    double m_rightAscension;
    double m_declination;
    double m_magnitude;
    string m_name;
};

vector<vector<CelestialObject>> strips(20);

istream& operator>>(istream& is, CelestialObject& obj) {
    double ra, dec, mag;
    string name;
    if (is >> ra >> dec >> mag >> name) {
        obj = CelestialObject(ra, dec, mag, name);
    }
    return is;
}

vector<CelestialObject> load_celestial_data(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        throw runtime_error("Error opening file");
    }

    vector<CelestialObject> objects;
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        CelestialObject obj(0.0, 0.0, 0.0, "");
        if (!(iss >> obj)) {
            throw runtime_error("Error parsing line in file");
        }
        objects.push_back(obj);
    }

    return objects;
}

const double STRIP_WIDTH = 20;

void divide_into_strips(const vector<CelestialObject>& objects) {

    vector<CelestialObject> sorted_objects(objects);
    sort(sorted_objects.begin(), sorted_objects.end(),
        [](const CelestialObject& a, const CelestialObject& b) {
            return a.getRightAscension() < b.getRightAscension();
        });

    int strip_idx = -1;
    double current_right_ascension = -1.0;
    for (const auto& obj : sorted_objects) {
        if (obj.getRightAscension() > current_right_ascension) {
            strip_idx++;
            current_right_ascension += STRIP_WIDTH;
        }
        if (strip_idx >= strips.size()) {
            break;
        }
        strips[strip_idx].push_back(obj);
    }

    for (auto& strip : strips) {
        sort(strip.begin(), strip.end(),
            [](const CelestialObject& a, const CelestialObject& b) {
                return a.getRightAscension() < b.getRightAscension();
            });
    }

    vector<vector<CelestialObject>> strip_data(strips.size());
    for (int i = 0; i < strips.size(); i++) {
        for (const auto& obj : strips[i]) {
            strip_data[i].push_back(obj);
        }
    }

    for (int i = 0; i < strips.size(); i++) {
        for (int j = 0; j < strips.size(); j++) {
            cout << strip_data[i][j].m_rightAscension << ",";
        }
    }
    cout << endl << "Sorting complete!" << endl;
}

struct CatalogObject {
    double ra;
    double dec;
};

struct ImageObject {
    double ra;
    double dec;
};

// Haversine formula to calculate the great-circle distance between two points on a sphere
   
double haversine(double ra1, double dec1, double ra2, double dec2)
{
    const double pi = 3.14159265358979323846;
    const double deg2rad = pi / 180.0;
    const double R = 6371e3; // radius of Earth in meters
    double d_ra = (ra2 - ra1) * deg2rad;
    double d_dec = (dec2 - dec1) * deg2rad;
    double a = sin(d_dec / 2) * sin(d_dec / 2) + cos(dec1 * deg2rad) * cos(dec2 * deg2rad) * sin(d_ra / 2) * sin(d_ra / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R * c;
    return d;
}

// Binary search to find the nearest object in a sorted vector
int binarySearch(const vector<CatalogObject> &objects, int start, int end, const ImageObject &image_object)
{
    if (start >= end)
    {
        return start;
    }
    int mid = start + (end - start) / 2;
    double mid_ra = objects[mid].ra;
    double image_ra = image_object.ra;
    if (mid_ra < image_ra)
    {
        return binarySearch(objects, mid + 1, end, image_object);
    }
    else
    {
        return binarySearch(objects, start, mid, image_object);
    }
}

int indrev()
{

   
    vector<CelestialObject> objects = load_celestial_data("input.csv");

    // Step a: Calculate the right ascension range of the image and find the strips that overlap with it
    double image_ra = 100.0;
    double ra_min = image_ra - 1.25;
    double ra_max = image_ra + 1.25;

    // Find the strips that overlap with the image
    int start_strip = -1;
    int end_strip = -1;
    for (int i = 0; i < objects.size(); i++) {
        double object_ra = objects[i].getRightAscension();
        if (object_ra >= ra_min && object_ra <= ra_max) {
            if (start_strip == -1) {
                start_strip = i;
            }
            end_strip = i;
        }
    }

    // Step b: Build the catalog for the objects that overlap with the image
    vector<CatalogObject> catalog;
    for (int i = start_strip; i <= end_strip; i++) {
        const auto& obj = objects[i];
        // Check if the object is within the right ascension range of the image
        if (obj.getRightAscension() >= ra_min && obj.getRightAscension() <= ra_max) {
            catalog.push_back({obj.getRightAscension(), obj.getDeclination()});
        }
    }

    // Step c: Sort the catalog by right ascension
    sort(catalog.begin(), catalog.end(),
         [](const CatalogObject& a, const CatalogObject& b) {
             return a.ra < b.ra;
         });

    // Step d: Find the nearest object in the catalog to each image object
    vector<ImageObject> image_objects = {
        {100.1, 20.5},
        {100.4, 20.9},
        {100.7, 21.3},
        {101.0, 21.7},
        {101.3, 22.1}
    };

    for (const auto& image_object : image_objects) {
        // Find the index of the nearest object in the catalog using binary search
        int index = binarySearch(catalog, 0, catalog.size() - 1, image_object);

        // Calculate the distance to the nearest object
        double distance = haversine(catalog[index].ra, catalog[index].dec, image_object.ra, image_object.dec);

        // Output the results
        cout << "Image object (" << image_object.ra << ", " << image_object.dec << ") is " << distance << " meters away from catalog object (" << catalog[index].ra << ", " << catalog[index].dec << ")" << endl;
    }

    return 0;
}