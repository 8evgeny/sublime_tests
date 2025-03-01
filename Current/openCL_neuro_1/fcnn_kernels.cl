//forward propagation
__kernel void compout(__global Node * nodes,
                      __global Node * prevnodes,
                      int softflag )
{
    const int n = get_global_size(0);
    const int i = get_global_id(0);
    float t = 0;

    for ( int j = 0; j < nodes[i].numberOfWeights; j++)
    {
        t += nodes[i].weights[j] * prevnodes[j].output;
    }
    t += 0.1; //bias
	
    if(softflag == 0)
    {
        switch(actflag)
        {
            case 0:nodes[i].output = sigmoid(t); break;
            case 1:nodes[i].output = mtanh(t); break;
            case 2:nodes[i].output = relu(t); break;
        }
    }
    else
    {
        nodes[i].output = t;
    }
}//END kernel void compout

//backward propagation
__kernel void backprophid(__global Node * nodes,
                          __global Node * prevnodes,
                          __global Node * nextnodes,
                          int nextnumNodes,
                          float a )
{
    const int n = get_global_size(0);
    const int i = get_global_id(0);
    float delta = 0;

    for (int j = 0; j !=nextnumNodes; j++)
    {
        delta += nextnodes[j].delta * nextnodes[j].weights[i];
//        delta *= nodes[i].output*(1 - nodes[i].output);
    }
	
    switch(actflag)
    {
        case 0: delta *= devsigmoid(nodes[i].output); break;
        case 1: delta *= devtanh(nodes[i].output); break;
        case 2: delta *= devrelu(nodes[i].output); break;
	}
    nodes[i].delta = delta;

    for (int j = 0; j != nodes[i].numberOfWeights; j++)
        nodes[i].weights[j] -= a*delta*prevnodes[j].output;
}//END kernel void backprophid

__kernel void softmax(__global Node * nodes,int nodesnum)
{
    const int i = get_global_id(0);
    float expsum=0;
    for (int j=0; j < nodesnum; j++)
        expsum += exp(nodes[j].output);

    nodes[i].output = exp(nodes[i].output)/expsum;

}//END kernel void softmax

__kernel void backpropout(__global Node * nodes,
                        __global Node * prevnodes,
                        __global float * targets,
                        float a,
                        int softflag)
{
    const int n = get_global_size(0);
    const int i = get_global_id(0);
	float delta=0;

    if(softflag == 1)
    {
		delta = nodes[i].output-targets[i];
	}
    else
    {
        switch(actflag)
        {
                case 0: delta = (nodes[i].output - targets[i]) * devsigmoid(nodes[i].output); break;
                case 1: delta = (nodes[i].output - targets[i]) * devtanh(nodes[i].output); break;
                case 2: delta = nodes[i].output - targets[i] * devrelu(nodes[i].output); break;
        }
	}

    for (int j = 0; j !=nodes[i].numberOfWeights; j++)
       nodes[i].weights[j] -= a * delta * prevnodes[j].output;

    nodes[i].delta = delta;

}//END kernel void backpropout



    


