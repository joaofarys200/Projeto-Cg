#include "catmullrom.h"


void buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}


void multMatrixVector(float m[4][4], float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
    }

}


void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

    // catmull-rom matrix
    float m[4][4] = {   {-0.5f,  1.5f, -1.5f,  0.5f},
                        { 1.0f, -2.5f,  2.0f, -0.5f},
                        {-0.5f,  0.0f,  0.5f,  0.0f},
                        { 0.0f,  1.0f,  0.0f,  0.0f}};


    for(int i = 0; i < 3; i++) {     // i = x, y, z
        float p[4] = {p0[i], p1[i], p2[i], p3[i]};
        float a[4];
        // Compute A = M * P
        multMatrixVector(m, p, a);
        
        pos[i] = powf(t,3.0) * a[0] + powf(t,2.0) * a[1] + t * a[2] + a[3];
        // Compute pos = T * A
        
        // compute deriv = T' * A
        deriv[i] = 3*powf(t,2.0) * a[0] + 2 * t * a[1] + a[2];
    }
}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv,std::vector<std::vector<float>> p) {

    int point_count=p.size();
    float t = gt * point_count; // this is the real global t
    int index = floor(t);  // which segment

    t = t - index; // where within  the segment

    // indices store the points
    int indices[4]; 
    indices[0] = (index + point_count-1)%point_count;   
    indices[1] = (indices[0]+1)%point_count;
    indices[2] = (indices[1]+1)%point_count; 
    indices[3] = (indices[2]+1)%point_count;

    float *p0 = p[indices[0]].data();
    float *p1 = p[indices[1]].data();
    float *p2 = p[indices[2]].data();
    float *p3 = p[indices[3]].data();
    
    // Call getCatmullRomPoint with pointers
    getCatmullRomPoint(t, p0, p1, p2, p3, pos, deriv);

}


void renderCatmullRomCurve(float* pos, float* deriv, std::vector<std::vector<float>> p, float draw) {

// draw curve using line segments with GL_LINE_LOOP
    if(draw==1){
        glBegin(GL_LINE_LOOP);
        float gt = 0;
        while (gt < 1) {
            getGlobalCatmullRomPoint(gt, pos, deriv,p);
            glVertex3f(pos[0],pos[1],pos[2]);
            gt += 1.0/100;
        }
        glEnd();
    }
    else{
        float gt = 0;
        while (gt < 1) {
            getGlobalCatmullRomPoint(gt, pos, deriv,p);
            gt += 1.0/100;
        }
    }
}