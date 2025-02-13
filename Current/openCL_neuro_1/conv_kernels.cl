__kernel  void convolve(__global float *image,
                      __global Filter* filters,
                      __global float * featMap,
                      int filterWidth,
                      int inWidth,
                      int featmapdim)
{
    const int xIn = get_global_id(0); //cols
    const int yIn = get_global_id(1); //rows
    const int z = get_global_id(2);   //filters
         
    float sum = 0;
    for (int r = 0; r < filterWidth; r++)
    {
        for (int c = 0; c < filterWidth; c++)
        {
         sum += filters[z].weights[c * filterWidth + r] * image[(xIn+c) + inWidth * (yIn + r)];
        //sum += filters[z].weights[(filterWidth-c) + filterWidth * (filterWidth - r)] * image[(xIn+c) + inWidth * (yIn+r)];
        }
    }

    sum += filters[z].bias;
    //featMap[(yIn+xIn*featmapdim +z*featmapdim*featmapdim)]=sum/(filterWidth*filterWidth);

    //featMap[(yIn+xIn*featmapdim +z*featmapdim*featmapdim)]=sigmoid(sum);
    switch(actflag)
    {
        case 0: featMap[(xIn+yIn*featmapdim +z*featmapdim*featmapdim)] =sigmoid(sum);break;
        case 1: featMap[(xIn+yIn*featmapdim +z*featmapdim*featmapdim)]=mtanh(sum);break;
        case 2: featMap[(xIn+yIn*featmapdim +z*featmapdim*featmapdim)]=relu(sum);break;
    }
}//END kernel  void convolve
 
__kernel void pooling(__global float* prevfeatMap,
                  __global float* poolMap,
                  __global int* indexes,
                  int Width,
                  int pooldim)
{
    const int xIn=get_global_id(0);
    const int yIn=get_global_id(1);
    const int z=get_global_id(2);

    float max = 0;
    int index = 0;
    for (int r = 0; r < 2; r++)
    {
        for (int c = 0; c < 2; c++)
        {
            if(prevfeatMap[(yIn+c) * Width * z +(xIn + r)] > max)
            {
                max = prevfeatMap[(yIn + c) * Width * z + (xIn + r)];
                index = c * 2 + r;
            }//END if(prevfeatMap[(yIn+c)*Width*z +(xIn+r)]>max)
        }//END for (int c = 0; c < 2; c++)
    }//END for (int r=0;r<2;r++)

    poolMap[(xIn + yIn * pooldim + z * pooldim * pooldim)] = max;
    indexes[(xIn + yIn * pooldim + z * pooldim * pooldim)] = index;

}//END kernel void pooling

__kernel void deltas(__global Node * nodes,
                   __global Node * nextnodes,
                   __global float * deltas,
                   __global int * indexes,
                   int dim,
                   int nextnumNodes,
                   int pooldim)
{
    const int xIn = get_global_id(0);
    const int yIn = get_global_id(1);
    const int z = get_global_id(2);

    int i = xIn + yIn * pooldim + z * pooldim * pooldim;

    float delta = 0;
    for (int j = 0; j !=nextnumNodes; j++)
        delta += nextnodes[j].delta * nextnodes[j].weights[i];

    switch(actflag)
    {
        case 0: delta *= devsigmoid(nodes[i].output); break;
        case 1: delta *= devtanh(nodes[i].output); break;
        case 2: delta *= devrelu(nodes[i].output); break;
    }

    for(int r=0; r < 2; r++)
    {
        for(int c = 0; c < 2; c++)
        {
            if((c * 2 + r) == indexes[i])
                deltas[(2 * xIn + r) + (2 * yIn + c) * dim + z * dim * dim] = delta;
        }
    }

}//END kernel void deltas

__kernel void rotatemat(__global float* source, __global float* destin, int dim)
{
    const int xIn = get_global_id(0);
    const int yIn = get_global_id(1);
    destin[xIn + dim * yIn] = source[(dim - xIn) + dim * (dim - yIn)];
}//END kernel void rotatemat
   
__kernel void backpropcnn(__global float* featMap,
                        __global float* deltas,
                        __global Filter* filters,
                        int featmapdim,
                        int imagedim,
                        int filterdim,
                        float a,global
                        float* Image)
{
    const int xIn = get_global_id(0);
    const int yIn = get_global_id(1);
    const int z = get_global_id(2);

    float sum = 0;
    for (int r = 0; r < featmapdim; r++)
    {
        for (int c = 0; c < featmapdim; c++)
        {
            sum += deltas[(c + r * featmapdim + z * featmapdim * featmapdim)] * Image[(xIn + r) + imagedim * (yIn + c)];
        }
    }

    filters[z].weights[(xIn + filterdim * yIn)] -= a * sum; ///(featmapdim*featmapdim) ;

    // filters[0].bias+=sum;///check this

}//END kernel void backpropcnn
   
__kernel void cnntoFcnn(__global float * poolMap,
                      __global Node * nodes,
                      int inputsize,
                      int mapindex)
{
    const int xIn = get_global_id(0);
    const int yIn = get_global_id(1);
    const int z = get_global_id(2);

    nodes[(xIn + yIn * inputsize + z * inputsize * inputsize)].output = poolMap[(xIn + yIn * inputsize + z * inputsize * inputsize)];
}


