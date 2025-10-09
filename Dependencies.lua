VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["ImGui"] = "%{wks.location}/RayTracing-Playgruond/3rdParty/ImGui"
IncludeDir["glm"] = "%{wks.location}/RayTracing-Playgruond/3rdParty/glm"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"