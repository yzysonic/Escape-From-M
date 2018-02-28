float3 view;

float4 BarrierPS(in float4 normal : NORMAL): COLOR
{
    float A = 0.5;
    float B = dot(-normalize(view), normalize(normal.xyz));
    float C = sqrt(1.0f - A * A * (1 - B * B));
    float Rs = (A * B - C) * (A * B - C) / ((A * B + C) * (A * B + C));
    float Rp = (A * C - B) * (A * C - B) / ((A * C + B) * (A * C + B));
    float alpha = (Rs + Rp) / 2.0f;

    //float3 vReflect = reflect(normalize(view), normalize(normal.xyz));

    float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    color.a = min(alpha + 0.20f, 1.0f);

    return color;
}