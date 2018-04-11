/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2018 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#ifndef IVW_CEFIMAGECONVERTER_H
#define IVW_CEFIMAGECONVERTER_H

#include <modules/webbrowser/webbrowsermoduledefine.h>
#include <modules/webbrowser/renderhandlergl.h>

#include <modules/opengl/texture/texture2d.h>
#include <modules/opengl/shader/shader.h>

#include <inviwo/core/ports/imageport.h>

namespace inviwo {

/* \class CefImageConverter
 * Flips vertical component of Cef output image.
 * TODO: Add picking id where image is not transparent.
 * Will enable better event handling since Cef does not say if an event has been used.
 * @see RenderHandlerGL
 */
class CefImageConverter {
public:
    CefImageConverter() = default;
    
    void convert(const Texture2D& fromCefOutput, ImageOutport &toInviwOutput);

protected:
     Shader shader_{"img_convert_cef.frag", true};  ///< Flip image y compoenent
};

}  // namespace inviwo

#endif  // IVW_WEBBROWSERCLIENT_H
