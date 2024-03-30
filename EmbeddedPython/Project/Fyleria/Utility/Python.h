// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_PYTHON_H_
#define _GECKO_UTILITY_PYTHON_H_

// External includes
#include <Python.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>
#include <pybind11/eval.h>
#include <pybind11/embed.h>

// Internal includes
#include "Utility/Types.h"

// PyBind defines
#define PyBindInitializeInterpreter pybind11::initialize_interpreter
#define PyBindFinalizeInterpreter pybind11::finalize_interpreter
#define PyBindAcquireScopedGIL pybind11::gil_scoped_acquire
#define PyBindReleaseScopedGIL pybind11::gil_scoped_release
#define PyBindRuntimeException pybind11::error_already_set
#define PyBindExec pybind11::exec
#define PyBindEval pybind11::eval
#define PyBindEvalFile pybind11::eval_file
#define PyBindModuleImport pybind11::module::import
#define PyBindCast pybind11::cast
#define PyBindObject pybind11::object
#define PyBindHandle pybind11::handle
#define PyBindModule pybind11::module
#define PyBindObject pybind11::object
#define PyBindClass pybind11::class_
#define PyBindConst pybind11::const_
#define PyBindEnum pybind11::enum_
#define PyBindInit pybind11::init
#define PyBindArg pybind11::arg
#define PyBindVector pybind11::bind_vector
#define PyBindMap pybind11::bind_map
#define PyBindOverloadCast pybind11::overload_cast
#define PyBindReturnTakeOwnership pybind11::return_value_policy::take_ownership
#define PyBindReturnCopy pybind11::return_value_policy::copy
#define PyBindReturnMove pybind11::return_value_policy::move
#define PyBindReturnRef pybind11::return_value_policy::reference
#define PyBindReturnRefInternal pybind11::return_value_policy::reference_internal
#define PyBindReturnAuto pybind11::return_value_policy::automatic
#define PyBindReturnAutoRef pybind11::return_value_policy::automatic_reference
#define PyBindMakeImplicitlyConvertible pybind11::implicitly_convertible

namespace Gecko
{

// Initialize python
Bool InitPython();

// Finalize python
Bool FinalizePython();

// Run python file
Bool RunPythonFile(const String& sFile);

// Run python command
Bool RunPythonCommand(const String& sCommand);

};

#endif
