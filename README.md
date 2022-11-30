# Zorang-Project-code
First we assume longitude on the x-axis and latidude on the y-axis next we find the corresponding angles b/w x-axis and line formed by restaurant coordinates and each address 
of coordinate respectively. Now each address is kept int sorted order on the basis on angles achieved by using the set. Now, Apply binary search to get maximum time taken by delivery boys.
Finding min delivery boys required by assigning each address to a delivery boy one by one. For a delivery boy, finding maximum address that he can deliever by iterating through addresses 
to order previously sorted ans comparing distance/time taken by a delievry boy to max time assumed and then storing and assigning address to delievery boy. Finally, taking
min delievery boys required till now for assumed max time and checking base conditions(i.e. <=10) and changing the max time accordingly.
