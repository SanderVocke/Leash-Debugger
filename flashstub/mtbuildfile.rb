application_project :flashstub, File.dirname(__FILE__) do |app|

  app.add_configuration :Debug,
    sources: ['src/**/*.c'],
    toolchain: toolchain(:arm_none_eabi_gcc,
      linker_script: 'linker.ld',
      include_paths: ['src', 'src/vendor']
    ),dependencies: [
      'CC3200_SDK_driverlib:SDK', 'CC3200_SDK_inc:SDK'
    ]

end
