__kernel void desaturate(__global __read_only uchar4 *pix,
                         __global __write_only uchar4 *pix_out)
{
	uint i = get_global_id(0);
    uchar gray = pix[i].x * 0.2126 + pix[i].y * 0.7152 + pix[i].z * 0.0722;
    pix_out[i].xyz = (uchar3)gray;
    pix_out[i].w = pix[i].w;
}
