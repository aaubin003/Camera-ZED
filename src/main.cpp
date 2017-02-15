/**********************************
Projet ZED
**********************************/

// Permet de supprimer l'erreur sur l'utilisation de la fonction "std::min" à la ligne 338 de objdetect.hpp (ZED sdk)
#define NOMINMAX

using namespace std;

#include <string>
#include <iostream>;
#include <stdio.h>;

// OpenCV
#include <opencv2/core/core.hpp>;
#include <opencv2/highgui/highgui.hpp>;
#include <opencv2/imgproc/imgproc.hpp>;
#include <opencv2/objdetect/objdetect.hpp>;

// ZED
#include <zed/Camera.hpp>;


// Autres
#include <Wingdi.h>;
#include <Windows.h>;


// Variables Globales :

// Input from keyboard
char keyboard = ' ';
cv::Mat ImageFamille = cv::imread("C:\\famille_nombreuse.jpg", CV_LOAD_IMAGE_COLOR);




cv::Mat affichageTetes(cv::Mat imageEntree)
{
	// ------------------- Traitement sur une image 2D ----------------------------------

	// Code from http://opencvexamples.blogspot.com/2013/10/face-detection-using-haar-cascade.html

	if (imageEntree.empty())
	{
		std::cout << "!!! Failed imread(): image not found" << std::endl;
		// don't let the execution continue, else imshow() will crash.
	};

	// Load Face cascade (.xml file)
	cv::CascadeClassifier face_cascade;
	std::string haarcascadepath = "D:\\Documents\\ENSC 2A\\Semestre 2\\Projet Info\\Projet\\CascadeClassifier\\haarcascade_frontalface_alt2.xml";
	if (!face_cascade.load(haarcascadepath))
	{
		printf("Erreur lors du chargement du Classifier");
	}

	// faces est le vecteur de Rectangle ou seront stockée les têtes détectées
	cv::vector<cv::Rect> faces;
	double scaleFactor = 1.1;
	int minNeighbors = 2, flags = 0;

	// Détection des têtes
	// Param1 - image : Matrice de type CV_8U qui contient l'image où les têtes seront détectées
	// Param2 - faces : Vecteur de rectangles qui vont contenir les têtes détectées
	// Param3 - scaleFactor : Détermine combien la taille de l'image est réduite à "each image scale" ?
	// Param4 - minNeighbors : Détermine combien de voisins chaque rectangle candidat doit avoir pour le retenir comme une tête
	// Param4 - flags : 
	// Param5 - minSize : La taille minimum d'un objet
	// Param4 - maxSize : La taille maximum d'un objet
	face_cascade.cv::CascadeClassifier::detectMultiScale(imageEntree, faces, scaleFactor, minNeighbors, flags | CV_HAAR_SCALE_IMAGE, cv::Size(10, 10), cv::Size(1000, 1000));

	// Dessine un cercle autour d'une seule tete

	if (faces.size() != 0)
	{
		cv::Point center(faces[0].x + faces[0].width*0.5, faces[0].y + faces[0].height*0.5);
		ellipse(imageEntree, center, cv::Size(faces[0].width*0.5, faces[0].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
	}

	// Dessine un cercle autour de chaque tête détectée
	/*
	for (int i = 0; i < faces.size(); i++)
	{
		int r = 30;
		cv::Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(imageEntree, center, cv::Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
	
	}*/

	

	return imageEntree;
	
}

cv::Mat imageTetes(cv::Mat imageEntree)
{
	cv::Mat imageSortie = imageEntree;
	if (imageEntree.empty())
	{
		std::cout << "!!! Failed imread(): image not found" << std::endl;
		// don't let the execution continue, else imshow() will crash.
	}
	// Load Face cascade (.xml file)
	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;

	std::string haarcascadepath = "D:\\Documents\\ENSC 2A\\Semestre 2\\Projet Info\\Projet\\CascadeClassifier\\haarcascade_frontalface_alt2.xml";
	std::string haarcascadepath2 = "D:\\Documents\\ENSC 2A\\Semestre 2\\Projet Info\\Projet\\CascadeClassifier\\ojoD.xml";
	std::string haarcascadepath3 = "D:\\Documents\\ENSC 2A\\Semestre 2\\Projet Info\\Projet\\CascadeClassifier\\ojoL.xml";
	if (!face_cascade.load(haarcascadepath))
	{
		printf("Erreur lors du chargement du Classifier");
	}
	cv::vector<cv::Rect> faces;
	double scaleFactor = 1.1;
	int minNeighbors = 2, flags = 0;

	// Détection des têtes
	// Param1 - image : Matrice de type CV_8U qui contient l'image où les têtes seront détectées
	// Param2 - faces : Vecteur de rectangles qui vont contenir les têtes détectées
	// Param3 - scaleFactor : Détermine combien la taille de l'image est réduite à "each image scale" ?
	// Param4 - minNeighbors : Détermine combien de voisins chaque rectangle candidat doit avoir pour le retenir comme une tête
	// Param4 - flags : 
	// Param5 - minSize : La taille minimum d'un objet
	// Param4 - maxSize : La taille maximum d'un objet
	face_cascade.cv::CascadeClassifier::detectMultiScale(imageEntree, faces, scaleFactor, minNeighbors, flags | CV_HAAR_SCALE_IMAGE, cv::Size(10, 10), cv::Size(1000, 1000));
	cv::Point center(faces[0].x + faces[0].width*0.5, faces[0].y + faces[0].height*0.5);
	int r = 30; // ratio d'agrandissement du rectangle

	if (faces.size() != 0)
	{
		cv::Point p1(faces[0].x - r, faces[0].y - r);
		cv::Point p2(r + faces[0].x + faces[0].width, r + faces[0].y + faces[0].height);
		cv::Rect R(p1, p2); //Create a rectangle
		imageSortie = imageEntree(R); //Crop the region of interest using above rectangle
	}
	
	return imageSortie;
}


int main(int argc, char** argv)
{
	while (keyboard != 'q')
	{
		cv::namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
		cv::imshow("MyWindow", imageTetes(ImageFamille));
	}
	

	// Initialize ZED color stream in HD and depth in Performance mode
	sl::zed::Camera* zed = new sl::zed::Camera(sl::zed::HD720);
	sl::zed::InitParams params;
	params.mode = sl::zed::QUALITY;
	sl::zed::ERRCODE err = zed->init(params);
	// Quit if an error occurred
	if (err != sl::zed::SUCCESS) {
		std::cout << "Unable to init the ZED:" << errcode2str(err) << std::endl;
		delete zed;
		return 1;
	}

	// Initialize color image and depth
	int width = zed->getImageSize().width;
	int height = zed->getImageSize().height;
	cv::Mat image(height, width, CV_8UC4, 1);
	cv::Mat depth(height, width, CV_8UC4, 1);

	// Create OpenCV windows
	cv::namedWindow("Image", cv::WINDOW_NORMAL);
	cv::namedWindow("Depth", cv::WINDOW_NORMAL);
	cv::namedWindow("Heads", cv::WINDOW_NORMAL);

	// Settings for windows
	cv::Size displaySize(720, 404);
	cv::Mat imageDisplay(displaySize, CV_8UC4);
	cv::Mat depthDisplay(displaySize, CV_8UC4);
	cv::Mat headsDisplay(displaySize, CV_8UC4);

	// Loop until 'q' is pressed
	while (keyboard != 'q') {

		

		// Grab frame and compute depth in FILL sensing mode
		if (!zed->grab(sl::zed::SENSING_MODE::FILL))
		{

			// Retrieve left color image
			sl::zed::Mat left = zed->retrieveImage(sl::zed::SIDE::LEFT);
			memcpy(image.data, left.data, width*height * 4 * sizeof(uchar));

			// Retrieve depth map
			sl::zed::Mat depthmap = zed->normalizeMeasure(sl::zed::MEASURE::DEPTH);
			memcpy(depth.data, depthmap.data, width*height * 4 * sizeof(uchar));
			
			// Display image in OpenCV window
			cv::resize(image, imageDisplay, displaySize);
			cv::imshow("Image", imageDisplay);

			// Display depth map in OpenCV window
			cv::resize(depth, depthDisplay, displaySize);
			cv::imshow("Depth",depthDisplay);
			
			// Display heads image in OpenCV window
			cv::resize(image, depthDisplay, displaySize);
			cv::imshow("Heads", affichageTetes(depthDisplay));

			// Affichage de la tete
			//cv::namedWindow("MyWindow", CV_WINDOW_NORMAL); //create a window with the name "MyWindow"
			//cv::Mat I = ImageFamille;
			//cv::imshow("MyWindow", ImageFamille); //display the image which is stored in the 'img' in the "MyWindow" window			
			
			


		}
		
		keyboard = cv::waitKey(30);

	}

	
	delete zed;
	
}