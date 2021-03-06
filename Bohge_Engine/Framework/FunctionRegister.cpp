//////////////////////////////////////////////////////////////////////////////////////
//
//						The Bohge Engine License (BEL)
//
//	Copyright (c) 2011-2014 Peng Zhao
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in 
//	all copies or substantial portions of the Software. And the logo of 
//	Bohge Engine shall be displayed full screen for more than 3 seconds 
//	when the software is started. Copyright holders are allowed to develop 
//	game edit based on Bohge Engine, The edit must be released under the MIT 
//	open source license if it is going to be published. In no event shall 
//	copyright holders be prohibited from using any code of Bohge Engine 
//	to develop any other analogous game engines.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//
//////////////////////////////////////////////////////////////////////////////////////
#include "FunctionRegister.h"
#include "IScriptSystem.h"



namespace BohgeEngine
{
	//RTTI_TYPE_IMPLEMENT( ScriptFunction );
	//-------------------------------------------------------------------------------------------------------
	FunctionRegister::FunctionRegister( void )
		:m_pResult(NULL),
		m_pResultGetter(NULL),
		m_pResultPusher(NULL),
		m_pFunction(NULL),
		m_eFunctionType( ScriptProperty::FT_MEMBER ),
		m_ID(0)
	{

	}
	//-------------------------------------------------------------------------------------------------------
	FunctionRegister::~FunctionRegister( void )
	{

	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::_CaculateID()
	{
		//和c++一样返回值不能做为重载的区分符号
		//这里可以用简单的循环去计算id，但是为了保证计算方法的一致（与脚本实现处，这里将其抽出来）
		switch( m_ArgumentRttis.size() )
		{
		case 0: m_ID = CaculateFunctionID();break;
		case 1: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID()
					);break;
		case 2: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID()
					);break;
		case 3: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID(),
					m_ArgumentRttis[2]->GetTypeID()
					);break;
		case 4: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID(),
					m_ArgumentRttis[2]->GetTypeID(),
					m_ArgumentRttis[3]->GetTypeID()
					);break;
		case 5: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID(),
					m_ArgumentRttis[2]->GetTypeID(),
					m_ArgumentRttis[3]->GetTypeID(),
					m_ArgumentRttis[4]->GetTypeID()
					);break;
		case 6: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID(),
					m_ArgumentRttis[2]->GetTypeID(),
					m_ArgumentRttis[3]->GetTypeID(),
					m_ArgumentRttis[4]->GetTypeID(),
					m_ArgumentRttis[5]->GetTypeID()
					);break;
		case 7: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID(),
					m_ArgumentRttis[2]->GetTypeID(),
					m_ArgumentRttis[3]->GetTypeID(),
					m_ArgumentRttis[4]->GetTypeID(),
					m_ArgumentRttis[5]->GetTypeID(),
					m_ArgumentRttis[6]->GetTypeID()
					);break;
		case 8: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID(),
					m_ArgumentRttis[2]->GetTypeID(),
					m_ArgumentRttis[3]->GetTypeID(),
					m_ArgumentRttis[4]->GetTypeID(),
					m_ArgumentRttis[5]->GetTypeID(),
					m_ArgumentRttis[6]->GetTypeID(),
					m_ArgumentRttis[7]->GetTypeID()
					);break;
		case 9: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID(),
					m_ArgumentRttis[2]->GetTypeID(),
					m_ArgumentRttis[3]->GetTypeID(),
					m_ArgumentRttis[4]->GetTypeID(),
					m_ArgumentRttis[5]->GetTypeID(),
					m_ArgumentRttis[6]->GetTypeID(),
					m_ArgumentRttis[7]->GetTypeID(),
					m_ArgumentRttis[8]->GetTypeID()
					);break;
		case 10: m_ID = CaculateFunctionID(
					m_ArgumentRttis[0]->GetTypeID(),
					m_ArgumentRttis[1]->GetTypeID(),
					m_ArgumentRttis[2]->GetTypeID(),
					m_ArgumentRttis[3]->GetTypeID(),
					m_ArgumentRttis[4]->GetTypeID(),
					m_ArgumentRttis[5]->GetTypeID(),
					m_ArgumentRttis[6]->GetTypeID(),
					m_ArgumentRttis[7]->GetTypeID(),
					m_ArgumentRttis[8]->GetTypeID(),
					m_ArgumentRttis[9]->GetTypeID()
					);break;
		default:ASSERT(false);
		}
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Result( const IScriptSystem& sys, const Rtti* rtti )
	{
		ASSERT(NULL==m_pResult);
		m_pResult = rtti;
		m_pResultGetter = sys.GetScriptResultValueFunction( rtti );
		m_pResultPusher = sys.GetScriptResultPushFunction( rtti );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3, const Rtti* rtti4 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentRttis.push_back(rtti4);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti4 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3, const Rtti* rtti4, const Rtti* rtti5 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentRttis.push_back(rtti4);
		m_ArgumentRttis.push_back(rtti5);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti4 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti5 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3, const Rtti* rtti4, const Rtti* rtti5, const Rtti* rtti6 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentRttis.push_back(rtti4);
		m_ArgumentRttis.push_back(rtti5);
		m_ArgumentRttis.push_back(rtti6);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti4 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti5 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti6 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3, const Rtti* rtti4, const Rtti* rtti5, const Rtti* rtti6, const Rtti* rtti7 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentRttis.push_back(rtti4);
		m_ArgumentRttis.push_back(rtti5);
		m_ArgumentRttis.push_back(rtti6);
		m_ArgumentRttis.push_back(rtti7);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti4 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti5 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti6 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti7 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3, const Rtti* rtti4, const Rtti* rtti5, const Rtti* rtti6, const Rtti* rtti7, const Rtti* rtti8 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentRttis.push_back(rtti4);
		m_ArgumentRttis.push_back(rtti5);
		m_ArgumentRttis.push_back(rtti6);
		m_ArgumentRttis.push_back(rtti7);
		m_ArgumentRttis.push_back(rtti8);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti4 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti5 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti6 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti7 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti8 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3, const Rtti* rtti4, const Rtti* rtti5, const Rtti* rtti6, const Rtti* rtti7, const Rtti* rtti8, const Rtti* rtti9 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentRttis.push_back(rtti4);
		m_ArgumentRttis.push_back(rtti5);
		m_ArgumentRttis.push_back(rtti6);
		m_ArgumentRttis.push_back(rtti7);
		m_ArgumentRttis.push_back(rtti8);
		m_ArgumentRttis.push_back(rtti9);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti4 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti5 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti6 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti7 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti8 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti9 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3, const Rtti* rtti4, const Rtti* rtti5, const Rtti* rtti6, const Rtti* rtti7, const Rtti* rtti8, const Rtti* rtti9, const Rtti* rtti10 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentRttis.push_back(rtti4);
		m_ArgumentRttis.push_back(rtti5);
		m_ArgumentRttis.push_back(rtti6);
		m_ArgumentRttis.push_back(rtti7);
		m_ArgumentRttis.push_back(rtti8);
		m_ArgumentRttis.push_back(rtti9);
		m_ArgumentRttis.push_back(rtti10);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti4 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti5 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti6 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti7 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti8 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti9 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti10 ) );
		_CaculateID();
	}
	//-------------------------------------------------------------------------------------------------------
	void FunctionRegister::Arguments( const IScriptSystem& sys, const Rtti* rtti1, const Rtti* rtti2, const Rtti* rtti3, const Rtti* rtti4, const Rtti* rtti5, const Rtti* rtti6, const Rtti* rtti7, const Rtti* rtti8, const Rtti* rtti9, const Rtti* rtti10, const Rtti* rtti11 )
	{
		ASSERT( 0 == m_ArgumentRttis.size() );
		m_ArgumentRttis.push_back(rtti1);
		m_ArgumentRttis.push_back(rtti2);
		m_ArgumentRttis.push_back(rtti3);
		m_ArgumentRttis.push_back(rtti4);
		m_ArgumentRttis.push_back(rtti5);
		m_ArgumentRttis.push_back(rtti6);
		m_ArgumentRttis.push_back(rtti7);
		m_ArgumentRttis.push_back(rtti8);
		m_ArgumentRttis.push_back(rtti9);
		m_ArgumentRttis.push_back(rtti10);
		m_ArgumentRttis.push_back(rtti11);
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti1 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti2 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti3 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti4 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti5 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti6 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti7 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti8 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti9 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti10 ) );
		m_ArgumentGetter.push_back( sys.GetScriptArgumentFunction( rtti11 ) );
		_CaculateID();
	}

}
