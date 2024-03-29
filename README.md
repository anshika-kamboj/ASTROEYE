
# ABSTRACT
Our Project “AstroEye” aims at dealing with problem related to astronomical/astrophysical data. We are aiming at providing solutions for problems like identifying the constellations present in night sky image, indexing the observed objects in space to the catalogue objects present, identifying the clusters of galaxies based on the linking length and finding the correlated distance based on given data and finding shortest path/route as per the hence derived distance.
<br>
<br>
# PROBLEMS STATEMENTS
<br>
AstroEye consists of 4 parts which help in different areas:
<br><br>


1.  <b>Constellation Identifier</b> – Based on an Image on night sky, converted to text format, wherein the period (.) represents empty space and asterisk (\*) represents the presence of star at that positon, this segment aims at identifying if there is any possible constellation being formed in the image by the stars.<br>
    *Approach Used:
Backtracking and Dynamic Programming*<br>

2.	 <b>Astronomical Object Indexer</b> - When astronomers analyze telescope images, they check whether newly observed objects appear in the catalog of known objects. To aid this process, this segment aims at providing the index of the observed object with respect to distance, from the nearest catalog object.<br>
      *Approach Used:
Divide and Conquer*<br>

3.	 <b>Cluster Identification</b> - Clusters are large groups of objects (here celestial) held together .Cluster identification helps the user to identify clusters just by giving the input as coordinates of celestial objects.<br>
      *Approach Used:
Backtracking*<br>

4.	<b>Distance between Galaxies Analyser</b>- In astrophysics, Correlation Functions (CF) is a measurement of the distribution of pairwise distances between astronomical objects. This segment helps in finding the distances via the Correlation Functions and find shortest paths as needed as per them.<br>
      *Approach Used:
Greedy Algorithm*<br>
<br>

# DETAILS ABOUT SEGMENTS
<br>


1.	<b>Constellation Identifier:</b>- In this segment we take a text file from user, which can be considered as a processed image, wherein the spaces in the night sky photo are represented by periods ‘.’ and stars are represented by asterisk ‘*’. Some constellations are stored in the code as objects of the class of constellations where in the coordinates of each succeeding star in the constellation w.r.t to the preceding star are stored. The processed image text file is traversed through and for any star encountered the possibility of it being the part of a constellation stored is checked by DFS as the succeeding stars are checked, this is by Backtracking checked for all the constellations. A failure of a star being a part of any of the constellations leads to it being stored in a table, so that if that star comes in path when checking for other stars it can be instantly rejected as a possibility based on the past results. Whenever a constellations is found the stars in the constellation are replaced by a predefined symbol and stored in a separate file.
<br>

2.	<b>Astronomical Object Indexer:</b> - The program is intended to simulate the process of matching celestial objects from a catalog to objects in an astronomical image. It reads in a CSV file containing information about celestial objects such as their right ascension, declination, magnitude, and name. Then, it divides the objects into strips based on their right ascension, with each strip covering a range of 20 degrees<practically 324000 strips>. Next, it calculates the right ascension range of an image and finds the strips that overlap with it. For each strip, it searches for objects within the right ascension range of the image using binary search. Finally, it calculates the distance between each object in the strip and the corresponding object in the image using the Haversine formula, and outputs the name of the object with the closest distance. The program uses the classes CelestialObject to store information about celestial objects, CatalogObject to store right ascension and declination of celestial objects, and ImageObject to store the right ascension and declination of objects in the image.
<br>
   
3.	<b>Cluster Identification:</b> - Density-based Spatial Clustering of Applications with Noise (DBSCAN) Algorithm<br>
->	For each object, a search is conducted to find all the neighboring objects within a specified radius (t).<br>
->	If an object has at least minobjects neighboring objects, it is considered a core object and added to a new cluster.<br>
->	Any neighboring objects that also have at least minobjects neighboring objects are added to the same cluster.<br>
->	The process is repeated until all objects are either part of a cluster or not considered in any group.<br>

4.	<b>Distance between Galaxies Analyser:</b>- Correlation Functions (CF) is a measurement of the distribution of pairwise distances between astronomical objects.<br>
