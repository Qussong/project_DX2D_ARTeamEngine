
struct VTX_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

cbuffer TRANSFORM : register(b0)
{
    float4 cbPocs;
    //int padd1;
    float4 cbScale;
    //int padd2;
};

VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPos = float4(_in.vPos * cbScale.xyz, 1.f);
    output.vPos.xyz += cbPocs.xyz;
    
    //output.vPos *= 5.5f;
    output.vColor = _in.vColor;
    
    return output;
}
