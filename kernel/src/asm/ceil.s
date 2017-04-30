.global ceil
.type ceil, @function
ceil:
    roundsd $0xa, %xmm0, %xmm0
    retq

