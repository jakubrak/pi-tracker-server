#ifndef PIPELINE_H
#define PIPELINE_H

#include <gst/gst.h>

class Pipeline
{
public:
    Pipeline();
    ~Pipeline();

    void play();

private:
    GstPipeline *pipe;
};

#endif // PIPELINE_H
