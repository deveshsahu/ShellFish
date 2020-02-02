#pragma once
namespace Graphics
{
	/**
	 * @brief Holds the details about an object that needs to be rendered
	 * 
	 * This object performs rendering as follows:
	 * 1. Binds associated VAO and VBOs
	 * 2. Binds any texture units 
	 * 3. Sets associated render state
	 * 4. Performs the draw call
	 * 5. Unbinds
	 */
	class RenderObject
	{
	public:
		RenderObject() {}

	protected:
		// Primitive type
		// Buffer Index
		// Render state id


	};
}