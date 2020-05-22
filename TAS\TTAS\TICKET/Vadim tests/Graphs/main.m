% graph builder

% input values
fileID = fopen('data.txt','r');
formatSpec = '%d %f %f %f %f';
sizeA = [5 Inf];

A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
A = A';


y = Graph_builder(A);



