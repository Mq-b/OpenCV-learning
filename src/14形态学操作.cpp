#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

// Function to demonstrate the
// closing morphological operator
void closingMorphological()
{
    // Reading the Image
    Mat image = imread( "新素材/1 (40).jpg", IMREAD_GRAYSCALE);
    if (!image.data) {
        cout << "Could not open or "
            << "find the image\n";
        return ;
    }

    int morph_size = 2;

    Mat element = getStructuringElement( MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
    Mat output;

    morphologyEx(image, output,
        MORPH_CLOSE, element,
        Point(-1, -1), 2);

    imshow("source", image);//对照
    imshow("Closing", output);
    waitKey();
}

int main(int argc, char** argv)
{
    closingMorphological();

    return 0;
}